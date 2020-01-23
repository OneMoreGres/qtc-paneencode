import common as c
from config import os_name
import shutil
import os

c.print('>> Downloading charsetdetect for {}'.format(os_name))

src_dir = os.path.abspath(__file__ + '/../../../third-party/charsetdetect')
if not os.path.exists(src_dir):
    c.run('git clone --depth 1 https://github.com/batterseapower/libcharsetdetect.git ' + src_dir)
else:
    c.print('Folder {} already exists'.format(src_dir))

build_dir = os.path.abspath(src_dir + '/../charsetdetect-build')
shutil.rmtree(build_dir, ignore_errors=True)
os.mkdir(build_dir)
os.chdir(build_dir)
arch = ''
if os_name.startswith('win'):
    arch = '-A ' + ('Win32' if os_name == 'win32' else 'x64')
c.run('cmake -DCMAKE_POSITION_INDEPENDENT_CODE=ON {} {}'.format(arch, src_dir))
c.run('cmake --build . --config Release')
