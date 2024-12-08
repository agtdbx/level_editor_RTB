project('RTB_editor', 'cpp',
  version : '0.1',
  default_options : ['warning_level=1', 'cpp_std=c++14'])



conf_data = configuration_data()
conf_data.set('DATA_PATH', get_option('prefix') + '/data')


executable('RTB_editor',
          'src/main.cpp',
          'src/Button.cpp',
          'src/Camera.cpp',
          'src/Editor.cpp',
          'src/EditorBar.cpp',
          'src/Functions.cpp',
          'src/Input.cpp',
          'src/Map.cpp',
          'src/Menu.cpp',
          'src/Select.cpp',
          'src/Switch.cpp',
          'src/Tuile.cpp',
          'src/Zone.cpp',
       build_rpath: '.',
           dependencies : [
              dependency('sdl2'),
              dependency('sdl2_image', static: true),
              dependency('sdl2_ttf', static: true),
              dependency('sdl2_mixer', static: true),
              dependency('jsoncpp', static: true),
              ],
			include_directories: include_directories('include'),
           install : true)

install_subdir('data', install_dir:'.')
