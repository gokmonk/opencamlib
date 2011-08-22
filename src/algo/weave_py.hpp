/*  
 *  Copyright 2010-2011 Anders Wallin (anders.e.e.wallin "at" gmail.com)
 *  
 *  This file is part of OpenCAMlib.
 *
 *  OpenCAMlib is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  OpenCAMlib is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with OpenCAMlib.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef WEAVE_PY_H
#define WEAVE_PY_H


#include "weave.hpp"

namespace ocl
{

namespace weave {
    
/// \brief python wrapper for VoronoiDiagram
///
class Weave_py : public Weave {
    public:
            Weave_py() : Weave() {};
    // PYTHON

        
        boost::python::list getVertices(VertexType t) const {
            boost::python::list plist;
            VertexItr it_begin, it_end, itr;
            boost::tie( it_begin, it_end ) = boost::vertices( g );
            for ( itr=it_begin ; itr != it_end ; ++itr ) {
                if ( g[*itr].type == t )
                    plist.append( g[*itr].position );
            }
            return plist;
        };
                    
        /// return CL-points to python
        boost::python::list getCLVertices() const {
            return getVertices( CL );
            /*
            boost::python::list plist;
            VertexItr it_begin, it_end, itr;
            boost::tie( it_begin, it_end ) = boost::vertices( g );
            for ( itr=it_begin ; itr != it_end ; ++itr ) {
                if ( g[*itr].type == CL )
                    plist.append( g[*itr].position );
            }
            return plist;
            */
        };
        /// return internal points to python
        boost::python::list getINTVertices() const {
            return getVertices( INT );
            /*
            boost::python::list plist;
            VertexItr it_begin, it_end, itr;
            boost::tie( it_begin, it_end ) = boost::vertices( g );
            for ( itr=it_begin ; itr != it_end ; ++itr ) {
                if ( g[*itr].type == INT )
                    plist.append( g[*itr].position );
            }
            return plist;
            */
        };
        /// return edges to python
        /// format is [ [p1,p2] , [p3,p4] , ... ]
        boost::python::list getEdges() const {
            boost::python::list edge_list;
            EdgeItr it_begin, it_end, itr;
            boost::tie( it_begin, it_end ) = boost::edges( g );
            for ( itr=it_begin ; itr != it_end ; ++itr ) { // loop through each edge

                boost::python::list point_list; // the endpoints of each edge
                Vertex v1 = boost::source( *itr, g  );
                Vertex v2 = boost::target( *itr, g  );
                point_list.append(g[v1].position);
                point_list.append(g[v2].position);
                edge_list.append(point_list);

            }
            return edge_list;
        };
        /// return loops to pyton
        boost::python::list py_getLoops() const {
            boost::python::list loop_list;
            BOOST_FOREACH( std::vector<Vertex> loop, loops ) {
                boost::python::list point_list;
                BOOST_FOREACH( Vertex v, loop ) {
                    point_list.append( g[v].position );
                }
                loop_list.append(point_list);
            }
            return loop_list;
        };
        
  

        
};

} // end weave namespace

} // end ocl namespace
#endif
// end voronoidiagram_py.h
