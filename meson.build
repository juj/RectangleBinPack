project('RectangleBinPack', 'cpp')

RectangleBinPack = static_library(
    'RectangleBinPack',

    sources : [
        'GuillotineBinPack.cpp',
        'MaxRectsBinPack.cpp',
        'Rect.cpp',
        'ShelfBinPack.cpp',
        'ShelfNextFitBinPack.cpp',
        'ShelfNextFitBinPack.cpp',
        'SkylineBinPack.cpp'
    ]
)

RectangleBinPack_dep = declare_dependency(
    link_with : RectangleBinPack,
    include_directories : include_directories('.')
)
