{
    'targets':
    [
        {
            'target_name': "node-sdl2_image",
            'include_dirs':
            [
                "<(module_root_dir)",
                "<!(node -e \"require('node-sdl2/include')\")",
                "<!(node -e \"require('nan')\")"
            ],
            'sources':
            [
                "node-sdl2_image.cc"
            ],
            'conditions':
            [
                [
                    'OS=="linux"',
                    {
                        'include_dirs': [ "/usr/local/include/SDL2", "/usr/local/include/SDL2_image" ],
                        'cflags': [ "<!@(sdl2-config --cflags)" ],
                        'ldflags': [ "<!@(sdl2-config --libs)" ],
                        'libraries': [ "-lSDL2", "-lSDL2_image", "-lpng" ]
                    }
                ],
                [
                    'OS=="mac"',
                    {
                        'include_dirs': [ "/usr/local/include/SDL2", "/usr/local/include/SDL2_image" ],
                        'cflags': [ "<!@(sdl2-config --cflags)" ],
                        'ldflags': [ "<!@(sdl2-config --libs)" ],
                        'libraries': [ "-L/usr/local/lib", "-lSDL2", "-lSDL2_image" ]
                    }
                ],
                [
                    'OS=="win"',
                    {
                        'include_dirs': [ "$(SDL2_ROOT)/include", "$(SDL2_IMAGE_ROOT)/include" ],
                        'libraries':
                        [
                            "$(SDL2_ROOT)/lib/x64/SDL2.lib",
                            "$(SDL2_IMAGE_ROOT)/lib/x64/SDL2_image.lib"
                        ],
                        'copies':
                        [
                            {
                                'destination': "${USERPROFILE}/bin",
                                'files':
                                [
                                    "$(SDL2_IMAGE_ROOT)/lib/x64/SDL2_image.dll",
                                    "$(SDL2_IMAGE_ROOT)/lib/x64/libjpeg-9.dll",
                                    "$(SDL2_IMAGE_ROOT)/lib/x64/libpng16-16.dll",
                                    "$(SDL2_IMAGE_ROOT)/lib/x64/libtiff-5.dll",
                                    "$(SDL2_IMAGE_ROOT)/lib/x64/libwebp-4.dll",
                                    "$(SDL2_IMAGE_ROOT)/lib/x64/zlib1.dll"
                                ]
                            }
                        ]
                    }
                ]
            ]
        }
    ]
}
