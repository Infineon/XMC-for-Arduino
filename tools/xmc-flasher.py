import argparse, subprocess, os, sys, re, tempfile, logging
from serial.tools.list_ports import comports
from xmc_data import xmc_master_data

version = '0.1.3'

jlinkexe = ''

# Set temporary file for jlink command file and output file
cmd_jlink =  os.path.join(tempfile.gettempdir(), 'cmd.jlink')
console_out = os.path.join(tempfile.gettempdir(), 'console.output')

def check_python_version():
    major = sys.version_info.major
    minor = sys.version_info.minor
    
    if major != 3:
        raise Exception(f"XMC Flasher requires Python3! Current version is {major}.{minor}")

def get_jlink_install_path():
    import winreg
    location = winreg.HKEY_CURRENT_USER
    try:
        key = winreg.OpenKeyEx(location,'SOFTWARE\\SEGGER\\J-Link',reserved=0,access=winreg.KEY_READ)
    except:
        raise Exception("SEGGER JLink not installed!")
    value = winreg.QueryValueEx(key,"InstallPath")
    winreg.CloseKey(key)
    return value[0]

def set_environment():
    global jlinkexe
    if sys.platform == 'linux' or sys.platform == 'linux2':
        jlinkexe = 'JLinkExe'
    elif sys.platform == 'win32' or sys.platform == 'cygwin':
        jlinkexe = rf"{get_jlink_install_path()}\jlink.exe"
    elif sys.platform == 'darwin':
        jlinkexe = 'JLinkExe'

def discover_jlink_devices():
    ports = comports()
    port_sn_list = []
    jlink_pattern = r'[Jj][-\s]?[Ll][Ii][Nn][Kk]'
    for p in ports:
        if re.search(jlink_pattern, p.description):
            port_sn_list.append((p.device, p.serial_number, p.description))

    return port_sn_list

def get_device_serial_number(port):
    port_sn_list = discover_jlink_devices()
    for device in port_sn_list:
        if device[0] == port and device[0] != None:
                return device[1]
    return None

def create_jlink_loadbin_command_file(binfile, enable_update):
    lines = []
    if not enable_update:
        lines.append('exec DisableAutoUpdateFW\n')
    lines += ['r\n', 'h\n', f'loadbin {binfile} 0x0\n', 'r\n', 'g\n', 'exit\n']
    with open(cmd_jlink,'w') as f:
        f.writelines(lines)
    return cmd_jlink

def create_jlink_mem_read_command_file(addr, bytes, enable_update):
    lines = []
    if not enable_update:
        lines.append('exec DisableAutoUpdateFW\n')
    lines += [f'mem {addr}, {bytes}\n', 'r\n', 'g\n', 'exit\n']
    with open(cmd_jlink,'w') as f:
        f.writelines(lines)
    return cmd_jlink

def create_jlink_erase_command_file(enable_update):
    lines = []
    if not enable_update:
        lines.append('exec DisableAutoUpdateFW\n')
    lines += ['r\n', 'h\n', 'erase\n', 'exit\n']
    with open(cmd_jlink,'w') as f:
        f.writelines(lines)
    return cmd_jlink

def remove_jlink_command_file(cmd_file):
    if os.path.exists(cmd_file):
        os.remove(cmd_file)

def remove_console_output_file(console_output_file):
    if os.path.exists(console_output_file):
        os.remove(console_output_file)        

def remove_backspaces(input_str):
    result = []
    for char in input_str:
        if char == '\b':
            if result:
                result.pop()
        else:
            result.append(char)
    return ''.join(result)

def jlink_commander(device, serial_num, cmd_file, console_output=False):
    jlink_cmd = [jlinkexe, '-autoconnect', '1','-exitonerror', '1', '-nogui', '1', '-device', device, '-SelectEmuBySN', serial_num, '-if', 'swd', '-speed', '4000', '-commandfile', cmd_file]

    #if console_output is True:
        #jlink_cmd.append('-log ') #todo: pipe this in a better way

    try:
        jlink_proc = subprocess.Popen(jlink_cmd, stdout=subprocess.PIPE, universal_newlines=True)
        if console_output is True:
            out, err = jlink_proc.communicate()
            with open(console_out, 'w') as f:
                f.write(remove_backspaces(out))
        else:
            for line in jlink_proc.stdout:
                print(remove_backspaces(line), end='')
        jlink_proc.wait()
    except:
        raise Exception("jlink error")
    
def process_console_output(string):
    with open(console_out,'r') as f:
        lines = f.readlines()
        lines[0].split('\n')
       
    for line in lines :
        if string in line and '=' in line:
            print(line)

def check_serial_number(serial_num):
    if serial_num == None:
        raise Exception("Device not found! Please check the serial port")

def get_mem_contents(addr, bytes, device, port, enable_update):
    try:
        serial_num = get_device_serial_number(port)
        check_serial_number(serial_num)
    except ValueError as e:
        logging.error(e)
    jlink_cmd_file = create_jlink_mem_read_command_file(addr, bytes, enable_update) # todo: comes from proper metafile
    jlink_commander(device, serial_num, jlink_cmd_file, True)
    remove_jlink_command_file(jlink_cmd_file)
    with open(console_out,'r') as f:
        lines = f.readlines()
        lines[0].split('\n')
    remove_console_output_file(console_out)
    reg_contents = ""   
    for line in lines :
        logging.debug(f"JLink Log: {line.strip()}")
        if addr in line and '=' in line:
            reg_contents = re.findall('[0-9,A-F]+', line)
            break
    if not reg_contents:
        logging.error(f"Wrong COM Port selected! {port}")
        raise Exception(f"Wrong COM Port selected! {port}\n")
    reg_contents.remove(addr) # remove the addr from the list, just keep reg contents
    reg_contents.reverse() # jlink returns LSB first, so reverse it to get MSB on the left side
    reg_contents = ''.join(reg_contents)
    return reg_contents

def read_master_data():
    return xmc_master_data

def find_device_by_value(value):
    master_data = read_master_data()
    for device, config in master_data.items():
        if config["IDCHIP"]["value"] == value:
            return device
    return None

def check_device(device, port, enable_update):
    master_data = read_master_data()
    # get value from reg
    device_value = get_mem_contents(master_data[device]['IDCHIP']['addr'], master_data[device]['IDCHIP']['size'], device, port, enable_update)
    device_value_masked = (int('0x'+device_value,16)) & (int('0x'+master_data[device]['IDCHIP']['mask'],16)) # take only those bits which are needed
    device_value_masked = f'{device_value_masked:x}'
    device_value_masked = device_value_masked.zfill(int(master_data[device]['IDCHIP']['size'])*2)
    logging.info(f"Selected Device is: {device}.")
    real_device = find_device_by_value(device_value_masked)
    #compare with stored master data
    if not real_device == device:
        if real_device != None:
            logging.info(f"Connected Device is: {real_device}.")
        logging.error(f"Device connected on port {port} does not match the selected device {device}.")
        raise Exception("Device connection mismatch.")

def check_mem(device, port, enable_update):
    if "XMC1" in device: 
        master_data = read_master_data()
        # get value from reg
        device_value = get_mem_contents(master_data[device]['FLSIZE']['addr'], master_data[device]['FLSIZE']['size'], device, port, enable_update)
        device_value = int('0x'+device_value,16) & int('0x0003f000',16) # bit 17 to bit 12 are needed
        device_value = device_value >> int(master_data[device]['FLSIZE']['bitposition_LSB'])
        flash_size = (device_value-1)*4 #flash size given by (ADDR-1)*4 
        flash_size = str(flash_size).zfill(4)
        logging.info(f"Flash size is: {int(flash_size)}kB.")
        # special case for XMC2GO-32kB variant, bypass check
        if "XMC1100" in device and int(flash_size) == 32:
            logging.warning("XMC2GO 32kB variant detected!")
            return
        #compare with selected device 
        if not flash_size == device.split('-')[1]:
            logging.error(f"Memory size of device connected {flash_size} does not match that of the selected device to flash: {device.split('-')[1]}")
            raise Exception("Memory size mismatch.")
    else: #XMC4 series
        master_data = read_master_data()
        # get value from reg
        device_value = get_mem_contents(master_data[device]['FLASH0_ID']['addr'], master_data[device]['FLASH0_ID']['size'], device, port, enable_update)     
        device_value_masked = (int('0x'+device_value,16)) & (int('0x'+master_data[device]['FLASH0_ID']['mask'],16)) # take only those bits which are needed
        device_value_masked = f'{device_value_masked:x}'
        device_value_masked = device_value_masked.zfill(int(master_data[device]['FLASH0_ID']['size'])*2)
        #compare with stored master data
        if not device_value_masked.upper() == master_data[device]['FLASH0_ID']['value']:
            logging.error(f"Memory size of device connected {flash_size} does not match that of the selected device to flash: {device.split('-')[1]}")
            raise Exception("Memory size mismatch.")
        
def check_port(port):
    serial_num = get_device_serial_number(port)
    if serial_num == None or port == None:
        port_sn_list = discover_jlink_devices()
        for port_sn in port_sn_list:
            if port_sn[1] != None:
                real_port = port_sn[0]
                logging.error(f"Device found:{port_sn_list}. You select {port}. Please select the correct port.")
                raise Exception("Wrong COM Port selected.")
    else:
        return
    
def upload(device, port, binfile, enable_jlink_log, enable_update):
    serial_num = get_device_serial_number(port)
    jlink_cmd_file = create_jlink_loadbin_command_file(binfile, enable_update)
    jlink_commander(device, serial_num, jlink_cmd_file, console_output=not enable_jlink_log)
    remove_jlink_command_file(jlink_cmd_file)

def erase(device, port, enable_update):
    serial_num = get_device_serial_number(port)
    jlink_cmd_file = create_jlink_erase_command_file(enable_update)
    jlink_commander(device, serial_num, jlink_cmd_file)
    remove_jlink_command_file(jlink_cmd_file)

def  debug(device, port, elfile):
    pass #TBD

def setup_logger(verbose=False):
    if verbose:
        level = logging.DEBUG
    else:
        level = logging.INFO
    logging.basicConfig(
        level=level,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%H:%M:%S"
    )

def parser():

    def main_parser_func(args):
        parser.print_help()

    def parser_upload_func(args):
        
        check_port(args.port)
        check_device(args.device, args.port, args.fw_jlink_update)
        check_mem(args.device, args.port, args.fw_jlink_update)
        upload(args.device, args.port, args.binfile, args.verbose, args.fw_jlink_update)
        if not args.verbose:
            with open(console_out, 'r') as f:
                found_loadbin = False
                for line in f:
                    if "J-Link>loadbin" in line:
                        found_loadbin = True
                    elif found_loadbin and "O.K." in line:
                        logging.info("Upload successful.")
                        break
                else:
                    logging.error("Upload failed.")
            remove_console_output_file(console_out)
        

    def parser_erase_func(args):
        erase(args.device, args.port, args.fw_jlink_update)

    class ver_action(argparse.Action):
        def __init__(self, option_strings, dest, **kwargs):
            return super().__init__(option_strings, dest, nargs=0, default=argparse.SUPPRESS, **kwargs)
        
        def __call__(self, parser, namespace, values, option_string, **kwargs):
            logging.info('xmc-flasher version: ' + version)
            parser.exit()

    # General parser
    parser  = argparse.ArgumentParser(description="xmc-flasher tool")
    parser.add_argument('-v','--version', action=ver_action, help='xmc-flasher version')
    subparser = parser.add_subparsers()
    parser.set_defaults(func=main_parser_func)

    # Upload parser
    parser_upload = subparser.add_parser('upload', description='Upload binary command')
    required_upload = parser_upload.add_argument_group('required arguments')
    required_upload.add_argument('-d','--device', type=str, help='jlink device name', required=True)
    required_upload.add_argument('-p','--port', type=str, nargs='?', const='', help='serial port')
    required_upload.add_argument('-f','--binfile', type=str, help='binary file to upload', required=True)
    required_upload.add_argument('--verbose', action='store_true', help='Enable verbose logging')
    parser_upload.add_argument('--no-fw-update', dest='fw_jlink_update', action='store_false', help='Disable JLink firmware update (default: enabled)')
    parser_upload.set_defaults(fw_jlink_update=True)
    parser_upload.set_defaults(func=parser_upload_func)

    # Erase parser
    parser_erase = subparser.add_parser('erase', description='erase command')
    required_erase = parser_erase.add_argument_group('required arguments')
    required_erase.add_argument('-d','--device', type=str, help='jlink device name', required=True)
    required_erase.add_argument('-p','--port', type=str, help='serial port', required=True)
    parser_erase.add_argument('--no-fw-update', dest='fw_jlink_update', action='store_false', help='Disable JLink firmware update (default: enabled)')
    parser_erase.set_defaults(fw_jlink_update=True)
    parser_erase.set_defaults(func=parser_erase_func)

    # debug_parser. 
    # TBD in future

    # Parse arguments
    args = parser.parse_args()
    
    # Logging option
    setup_logger(verbose=args.verbose)
    if args.verbose:
        sys.tracebacklimit = None  # Enable full traceback
    else:
        sys.tracebacklimit = 0  # Disable traceback
    
    # Parser call
    args.func(args) 

if __name__ == "__main__":
    set_environment()
    check_python_version()
    parser()
