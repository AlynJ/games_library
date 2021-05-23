#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp> //for wrapping the std::vector
#include <vector>
#include "game.h"

namespace py=boost::python;

BOOST_PYTHON_MODULE(gamewrapper){

  py::class_<std::vector<std::vector<int> > > ("Pyvec2")
     .def(py::vector_indexing_suite<std::vector<std::vector<int> > >());

  py::class_<std::vector<int> > ("Pyvec")
     .def(py::vector_indexing_suite<std::vector<int> >());

  py::class_<Minesweeper>("Minesweeper",py::init<>())
    .def("mine_init", &Minesweeper::mine_init)
    .def("display_el", &Minesweeper::display_el)
    .def("minefield_el", &Minesweeper::minefield_el)
    .def("get_imx", &Minesweeper::get_imx)
    .def("get_jmx", &Minesweeper::get_jmx)
    .def("get_N", &Minesweeper::get_N)
    .def("get_safe", &Minesweeper::get_safe)
    .def("user_input", &Minesweeper::user_input)
    .def("win_loss", &Minesweeper::win_loss)
    .def("update", &Minesweeper::update)
    .def("hints", &Minesweeper::hints)
    .def("init_minefield", &Minesweeper::init_minefield)
    .def("disp_minefield", &Minesweeper::disp_minefield)
    .def("zero", &Minesweeper::zero)
    .def("reveal_zeros", &Minesweeper::reveal_zeros)
    //.add_property("mfld",&Minesweeper::mfld)
    //.add_property("dsp",&Minesweeper::dsp)
    //.add_property("again",&Minesweeper::again)
   // .add_property("win",&Minesweeper::win)
   // .add_property("imx",&Minesweeper::imx)
   // .add_property("jmx",&Minesweeper::jmx)
   // .add_property("x",&Minesweeper::x)
   // .add_property("y",&Minesweeper::y)
   // .add_property("N",&Minesweeper::N)
   // .add_property("play",&Minesweeper::play)
   // .add_property("safe",&Minesweeper::safe)
  ;


}
