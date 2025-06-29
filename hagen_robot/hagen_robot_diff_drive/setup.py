import os 
from glob import glob 
from setuptools import setup

package_name = 'hagen_robot_diff_drive'

cur_directory_path = os.path.abspath(os.path.dirname(__file__))

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name,'launch'), glob('launch/*.launch.py')),
        (os.path.join('share', package_name,'worlds/'), glob('./worlds/*')),
        (os.path.join('share', package_name,'models/'), glob('./worlds/*')),
        (os.path.join('share', package_name,'models/hagen_robot_model/materials/textures'), glob('models/hagen_robot_model/materials/textures/*')),
        (os.path.join('share', package_name,'models/hagen_robot_model/meshes'), glob('models/hagen_robot_model/meshes/*')),
        (os.path.join('share', package_name,'models/hagen_robot_model/'), glob('./models/hagen_robot_model/*.sdf')),
        (os.path.join('share', package_name,'models/hagen_robot_model/'), glob('./models/hagen_robot_model/*.config')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='TODO',
    maintainer_email='TODO@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
          'spawn_robot = hagen_robot_diff_drive.spawn_robot:main'
        ],
    },
)