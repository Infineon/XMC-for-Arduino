import argparse, serial, subprocess, os, sys
from serial.tools.list_ports import comports

version = '0.1.0'

jlinkexe = ''

def set_environment():
    global jlinkexe
    if sys.platform == 'linux' or sys.platform == 'linux2':
        jlinkexe = 'JLinkExe'
    elif sys.platform == 'win32' or sys.platform == 'cygwin':
        jlinkexe = 'jlink'
    elif sys.platform == 'darwin':
        jlinkexe = 'jlink'
        print('warning: mac os not validated')
        #raise Exception('mac os not supported?')

def discover_devices():
    ports = comports()
    port_sn_list = []
    for p in ports:
        port_sn_list.append((p.device, p.serial_number))

    return port_sn_list

def get_device_serial_number(port):
    port_sn_list = discover_devices()
    for device in port_sn_list:
        if device[0] == port:
            return device[1]
    
    return None

def create_jlink_loadbin_command_file(binfile):
    cmd_jlink = 'cmd.jlink'
    cmd_load_bin = 'loadbin ' + binfile + ' 0x0\n'
    with open(cmd_jlink,'w') as f:
        f.writelines(['r\n', 'h\n', cmd_load_bin, 'r\n', 'g\n', 'exit\n'])

    return cmd_jlink

def create_jlink_erase_command_file():
    cmd_jlink = 'cmd.jlink'
    with open(cmd_jlink,'w') as f:
        f.writelines(['r\n', 'h\n', 'erase\n', 'exit\n'])

    return cmd_jlink

def remove_jlink_command_file(cmd_file):
    if os.path.exists(cmd_file):
        os.remove(cmd_file)

def jlink_commander(device, serial_num, cmd_file):
    jlink_cmd = [jlinkexe, '-autoconnect', '1','-exitonerror', '1', '-nogui', '1', '-device', device, '-selectemubysn', serial_num, '-if', 'swd', '-speed', '4000', '-commandfile', cmd_file]

    try:
        jlink_proc = subprocess.Popen(jlink_cmd)
        jlink_proc.wait()
    except:
        raise Exception("jlink error")

def upload(device, port, binfile):
    serial_num = get_device_serial_number(port)
    jlink_cmd_file = create_jlink_loadbin_command_file(binfile)
    jlink_commander(device, serial_num, jlink_cmd_file)
    remove_jlink_command_file(jlink_cmd_file)

def erase(device, port):
    serial_num = get_device_serial_number(port)
    jlink_cmd_file = create_jlink_erase_command_file()
    jlink_commander(device, serial_num, jlink_cmd_file)
    remove_jlink_command_file(jlink_cmd_file)

def  debug(device, port, elfile):
    pass #TBD

def parser():

    def main_parser_func(args):
        parser.print_help()

    def parser_upload_func(args):
        upload(args.device, args.port, args.binfile)

    def parser_erase_func(args):
        erase(args.device, args.port)

    class ver_action(argparse.Action):
        def __init__(self, option_strings, dest, **kwargs):
            return super().__init__(option_strings, dest, nargs=0, default=argparse.SUPPRESS, **kwargs)
        
        def __call__(self, parser, namespace, values, option_string, **kwargs):
            print('xmc-upload version: ' + version)
            parser.exit()

    # General parser
    parser  = argparse.ArgumentParser(description="xmc-upload tool")
    parser.add_argument('-v','--version', action=ver_action, help='xmc-upload version')
    subparser = parser.add_subparsers()
    parser.set_defaults(func=main_parser_func)

    # Upload parser
    parser_upload = subparser.add_parser('upload', description='Upload binary command')
    required_upload = parser_upload.add_argument_group('required arguments')
    required_upload.add_argument('-d','--device', type=str, help='jlink device name', required=True)
    required_upload.add_argument('-p','--port', type=str, help='serial port', required=True)
    required_upload.add_argument('-f','--binfile', type=str, help='binary file to upload', required=True)
    parser_upload.set_defaults(func=parser_upload_func)

    # Debug parser
    parser_erase = subparser.add_parser('erase', description='erase command')
    required_erase = parser_erase.add_argument_group('required arguments')
    required_erase.add_argument('-d','--device', type=str, help='jlink device name', required=True)
    required_erase.add_argument('-p','--port', type=str, help='serial port', required=True)
    parser_erase.set_defaults(func=parser_erase_func)

    # debug_parser. 
    # TBD in future

    # Parser call
    args = parser.parse_args()
    args.func(args) 

if __name__ == "__main__":
    set_environment()
    parser()

