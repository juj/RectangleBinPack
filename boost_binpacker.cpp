#include <boost/python.hpp>
#include <vector>
#include "./MaxRectsBinPack.h"
#include "./GuillotineBinPack.h"
#include "./ShelfBinPack.h"
#include "./SkylineBinPack.h"
#include <cstdio>

using namespace boost::python;

BOOST_PYTHON_MODULE(boost_binpacker_ext)
{
	  using namespace rbp;

    class_<Rect>("Rect")
        .add_property("x", &Rect::x)
        .add_property("y", &Rect::y)
        .add_property("width", &Rect::width)
        .add_property("height", &Rect::height)
    ;

    // MaxRectBinpack
    enum_<MaxRectsBinPack::FreeRectChoiceHeuristic>("MaxRectsFreeRectChoiceHeuristic")
        .value("RectBestShortSideFit", MaxRectsBinPack::RectBestShortSideFit)
        .value("RectBestLongSideFit", MaxRectsBinPack::RectBestLongSideFit)
        .value("RectBestAreaFit", MaxRectsBinPack::RectBestAreaFit)
        .value("RectBottomLeftRule", MaxRectsBinPack::RectBottomLeftRule)
        .value("RectContactPointRule", MaxRectsBinPack::RectContactPointRule)
    ;

    Rect (MaxRectsBinPack::*MaxRectsInsert)(int, int, MaxRectsBinPack::FreeRectChoiceHeuristic) = &MaxRectsBinPack::Insert;

    class_<MaxRectsBinPack>("MaxRectsBinPack", init<int, int>())
        .def(init<>())
        .def("init", &MaxRectsBinPack::Init) 
        .def("insert", MaxRectsInsert)
        .def("occupancy", &MaxRectsBinPack::Occupancy)
    ;

    // GuillotineBinPack
    enum_<GuillotineBinPack::FreeRectChoiceHeuristic>("GuillotineFreeRectChoiceHeuristic")
        .value("RectBestAreaFit", GuillotineBinPack::RectBestAreaFit)
        .value("RectBestShortSideFit", GuillotineBinPack::RectBestShortSideFit)
        .value("RectBestLongSideFit", GuillotineBinPack::RectBestLongSideFit)
        .value("RectWorstAreaFit", GuillotineBinPack::RectWorstAreaFit)
        .value("RectWorstShortSideFit", GuillotineBinPack::RectWorstShortSideFit)
        .value("RectWorstLongSideFit", GuillotineBinPack::RectWorstLongSideFit)
    ;
    enum_<GuillotineBinPack::GuillotineSplitHeuristic>("GuillotineSplitHeuristic")
        .value("SplitShorterLeftoverAxis", GuillotineBinPack::SplitShorterLeftoverAxis)
        .value("SplitLongerLeftoverAxis", GuillotineBinPack::SplitLongerLeftoverAxis)
        .value("SplitMinimizeArea", GuillotineBinPack::SplitMinimizeArea)
        .value("SplitMaximizeArea", GuillotineBinPack::SplitMaximizeArea)
        .value("SplitShorterAxis", GuillotineBinPack::SplitShorterAxis)
        .value("SplitLongerAxis", GuillotineBinPack::SplitLongerAxis)
    ;

    Rect (GuillotineBinPack::*GuillotineInsert)(int, int, bool, GuillotineBinPack::FreeRectChoiceHeuristic, GuillotineBinPack::GuillotineSplitHeuristic) = &GuillotineBinPack::Insert;

    class_<GuillotineBinPack>("GuillotineBinPack", init<int, int>())
        .def(init<>())
        .def("init", &GuillotineBinPack::Init) 
        .def("insert", GuillotineInsert)
        .def("occupancy", &GuillotineBinPack::Occupancy)
    ;

    // ShelfBinPack
    enum_<ShelfBinPack::ShelfChoiceHeuristic>("ShelfChoiceHeuristic")
        .value("ShelfNextFit", ShelfBinPack::ShelfNextFit)
        .value("ShelfFirstFit", ShelfBinPack::ShelfFirstFit)
        .value("ShelfBestAreaFit", ShelfBinPack::ShelfBestAreaFit)
        .value("ShelfWorstAreaFit", ShelfBinPack::ShelfWorstAreaFit)
        .value("ShelfBestHeightFit", ShelfBinPack::ShelfBestHeightFit)
        .value("ShelfBestWidthFit", ShelfBinPack::ShelfBestWidthFit)
        .value("ShelfWorstWidthFit", ShelfBinPack::ShelfWorstWidthFit)
    ;

    class_<ShelfBinPack>("ShelfBinPack", init<int, int, bool>())
        .def(init<>())
        .def("init", &ShelfBinPack::Init) 
        .def("insert", &ShelfBinPack::Insert)
        .def("occupancy", &ShelfBinPack::Occupancy)
    ;

	// SkylineBinPack
	  enum_<SkylineBinPack::LevelChoiceHeuristic>("SkylineLevelChoiceHeuristic")
        .value("LevelBottomLeft", SkylineBinPack::LevelBottomLeft)
        .value("LevelMinWasteFit", SkylineBinPack::LevelMinWasteFit)
    ;

	Rect (SkylineBinPack::*SkylineInsert)(int, int, SkylineBinPack::LevelChoiceHeuristic) = &SkylineBinPack::Insert;

    class_<SkylineBinPack>("SkylineBinPack", init<int, int, bool>())
        .def(init<>())
        .def("init", &SkylineBinPack::Init) 
        .def("insert", SkylineInsert)
        .def("occupancy", &SkylineBinPack::Occupancy)
    ;
 }
