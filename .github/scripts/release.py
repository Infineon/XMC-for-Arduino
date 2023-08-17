
import argparse, copy, hashlib, json, re, requests, os, shutil

version = '0.1.0'

xmc_ino_root_path = os.path.relpath(os.path.join(os.path.join(os.getcwd(), os.pardir), os.pardir))
build_dir_name = 'pkg_build'
pkg_assets_build_path = os.path.join(xmc_ino_root_path , build_dir_name)

def strip_prefix_from_version(version):
    return re.sub(r'[vV]', '', version)

def mkdir_package_dir(version):
    semver = strip_prefix_from_version(version)
    pkg_name = "XMC_IFX_" + semver
    pkg_build_path = os.path.join(pkg_assets_build_path, pkg_name)
    os.mkdir(pkg_build_path)

    return pkg_name

def build_package(pkg_name):
    pkg_build_path = os.path.join(pkg_assets_build_path, pkg_name)

    dirs_to_copy = [ 
        'cores',
        'libraries',
        'tools',
    	'variants'
    ]

    files_to_copy = [
        'boards.txt',
        'keywords.txt',
        'package.json',
        'platform.txt',
        'LICENSE.md',
        'README.md'
    ]

    for dir in dirs_to_copy:
        shutil.copytree(os.path.join(xmc_ino_root_path, dir), os.path.join(pkg_build_path, dir))

    for file in files_to_copy:
        shutil.copyfile(os.path.join(xmc_ino_root_path, file), os.path.join(pkg_build_path, file))

def zip_package(pkg_name):
    pkg_build_path = os.path.join(pkg_assets_build_path, pkg_name)
    shutil.make_archive(pkg_build_path, 'zip', pkg_assets_build_path, pkg_name)

def get_package_size(pkg):
    return os.path.getsize(pkg)

def get_package_sha256(pkg):
    with open(pkg,"rb") as f:
        bytes = f.read() 
        hash = hashlib.sha256(bytes).hexdigest()

    return hash

def get_latest_package_index_json():
    return requests.get('https://github.com/Infineon/XMC-for-Arduino/releases/latest/download/package_infineon_index.json').json()

def get_platform_data_struct_copy(pkg_index):
    return copy.deepcopy(pkg_index['packages'][0]['platforms'][0])

def set_new_platform_data_fields(platform_data, pkg_name, version):
    semver = strip_prefix_from_version(version)
    platform_data['version'] = str(semver)
    archive_file_name = str(pkg_name) + ".zip"
    platform_data['archiveFileName'] = archive_file_name
    platform_data['url'] = "https://github.com/Infineon/XMC-for-Arduino/releases/download/" + str(version) + "/" + str(archive_file_name)
    platform_data['checksum'] ="SHA-256:" + str(get_package_sha256(os.path.join(pkg_assets_build_path, archive_file_name)))
    platform_data['size'] = str(get_package_size(os.path.join(pkg_assets_build_path, archive_file_name)))

def add_new_platform_to_package_index(pkg_index, new_platform):    
    pkg_index['packages'][0]['platforms'].insert(0, new_platform)

def make_package_index_file(pkg_index):
    pkg_index_json_obj = json.dumps(pkg_index, indent=2)
    pkg_index_w_path = os.path.join(pkg_assets_build_path, "package_infineon_index.json")
    with open(pkg_index_w_path, "w") as pkg_file:
        pkg_file.write(pkg_index_json_obj)

def build_package_index_json(pkg_name, version):
    package_index = get_latest_package_index_json()
    new_platform_data = get_platform_data_struct_copy(package_index)
    set_new_platform_data_fields(new_platform_data, pkg_name, version)
    add_new_platform_to_package_index(package_index, new_platform_data)
    make_package_index_file(package_index)

def build_release_assets(version):
    os.mkdir(pkg_assets_build_path)
    pkg_name = mkdir_package_dir(version)
    build_package(pkg_name)
    zip_package(pkg_name)
    build_package_index_json(pkg_name, version)

def parser():

    def main_parser_func(args):
        parser.print_help()

    def parser_build_release_assets_func(args):
        global xmc_ino_root_path
        global pkg_build_path
        xmc_ino_root_path = args.root_path
        pkg_build_path = args.build_path
        build_release_assets(args.version)

    class ver_action(argparse.Action):
        def __init__(self, option_strings, dest, **kwargs):
            return super().__init__(option_strings, dest, nargs=0, default=argparse.SUPPRESS, **kwargs)
        
        def __call__(self, parser, namespace, values, option_string, **kwargs):
            print('xmc-release version: ' + version)
            parser.exit()

    # General parser
    parser  = argparse.ArgumentParser(description="xmc-release tool")
    parser.add_argument('-v','--version', action=ver_action, help='xmc-release version')
    subparser = parser.add_subparsers()
    parser.set_defaults(func=main_parser_func)

    # Release parser
    parser_release = subparser.add_parser('build-release', description='Build package release assets')
    parser_release.add_argument('version', type=str, help='Package release version (semver x.y.z)')
    parser_release.add_argument('-r','--root-path', type=str, default=xmc_ino_root_path, help='Path to the XMC-for-Arduino root path')
    parser_release.add_argument('-b','--build-path', type=str, default=pkg_assets_build_path, help='Path to build package')
    parser_release.set_defaults(func=parser_build_release_assets_func)

    args = parser.parse_args()
    args.func(args)

if __name__ == "__main__":
    parser()