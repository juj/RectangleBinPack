import boost_binpacker_ext

max_rect_packer = boost_binpacker_ext.MaxRectsBinPack(100, 100)
second_packer = boost_binpacker_ext.MaxRectsBinPack()
second_packer.init(100, 200)

heuristic = boost_binpacker_ext.MaxRectsFreeRectChoiceHeuristic.RectBestShortSideFit
print max_rect_packer.insert(20, 20, heuristic).height # '20': fits
print max_rect_packer.insert(200, 20, heuristic).height # '0': does not fit

guillotine_packer = boost_binpacker_ext.GuillotineBinPack(100, 100)
heuristic = boost_binpacker_ext.GuillotineFreeRectChoiceHeuristic.RectBestShortSideFit
splitmethod = boost_binpacker_ext.GuillotineSplitHeuristic.SplitMinimizeArea
print guillotine_packer.insert(20, 20, True, heuristic, splitmethod).height # '20': fits

shelf_packer = boost_binpacker_ext.ShelfBinPack(100, 100, True)
heuristic = boost_binpacker_ext.ShelfChoiceHeuristic.ShelfNextFit
print shelf_packer.insert(20, 20, heuristic).height # '20': fits

skyline_packer = boost_binpacker_ext.SkylineBinPack(100, 100, True)
heuristic = boost_binpacker_ext.SkylineLevelChoiceHeuristic.LevelBottomLeft
print skyline_packer.insert(20, 20, heuristic).height # '20': fits
