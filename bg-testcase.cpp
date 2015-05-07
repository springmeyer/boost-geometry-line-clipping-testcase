#include <iostream>
#include <deque>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/box.hpp>

#include <boost/foreach.hpp>

/*

clang++ -o bg bg-testcase.cpp -Imason_packages/.link/include/ -std=c++11 -O0 -DDEBUG;./bg

*/

int main()
{
    typedef boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<std::int64_t> > polygon;
    typedef boost::geometry::model::linestring<boost::geometry::model::d2::point_xy<std::int64_t> > line;
    typedef boost::geometry::model::d2::point_xy<std::int64_t> point;

    // the line we will clip
    line clippable_line;
    boost::geometry::read_wkt(
        "LINESTRING(-20 0, 20 0)", clippable_line);

    // polygon representing clipping box
    polygon clip_polygon;
    boost::geometry::read_wkt(
        "POLYGON((-10 -10,-10 10,10 10,10 -10,-10 -10))", clip_polygon);


    // Clipping the line via the polygon works
    {
        std::deque<line> output;
        boost::geometry::intersection(clip_polygon, clippable_line, output);

        std::cout << "clipped via polygon:\n\t";
        for (auto const& l : output)
        {
            std::cout << boost::geometry::wkt(l) << std::endl;
        }        
    }

    // "box" type representing clipping box
    boost::geometry::model::box<point> clip_box;


    // Clipping the line via the box does not
    {
        boost::geometry::envelope(clip_polygon, clip_box);
        std::deque<line> output;
        boost::geometry::intersection(clip_box, clippable_line, output);

        std::cout << "clipped via box:\n\t";
        for (auto const& l : output)
        {
            std::cout << boost::geometry::wkt(l) << std::endl;
        }        
    }
    return 0;
}