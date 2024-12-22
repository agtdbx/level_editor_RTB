project('RTB_editor', 'cpp',
  version : '0.1',
  default_options : [
    'warning_level=1',
    'cpp_std=c++14',
    'default_library=static'
  ])


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
            dependency('sdl2_image'),
            dependency('sdl2_ttf'),
            dependency('sdl2_mixer'),
            dependency('jsoncpp'),
            ],
          include_directories: include_directories('include'),
          install : true)

install_subdir('data', install_dir:'.')
