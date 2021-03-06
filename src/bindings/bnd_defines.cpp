#include "bindings.h"

class BND_DocObjects {};

class BND_MeshTypeNamespace {};

#if defined(ON_PYTHON_COMPILE)
namespace py = pybind11;
void initDefines(pybind11::module& m)
{
  py::class_<ON_Line>(m, "Line")
    .def(py::init<ON_3dPoint, ON_3dPoint>())
    .def_readwrite("From", &ON_Line::from)
    .def_readwrite("To", &ON_Line::to)
    .def_property_readonly("IsValid", &ON_Line::IsValid)
    .def_property_readonly("Length", &ON_Line::Length)
    .def_property_readonly("Direction", &ON_Line::Direction)
    .def_property_readonly("UnitTangent", &ON_Line::Tangent)
    .def("PointAt", &ON_Line::PointAt)
    ;

  py::enum_<ON::object_mode>(m, "ObjectMode")
    .value("Normal", ON::object_mode::normal_object)
    .value("Hidden", ON::object_mode::hidden_object)
    .value("Locked", ON::object_mode::locked_object)
    .value("InstanceDefinitionObject", ON::object_mode::idef_object)
    ;

  py::enum_<ON::object_color_source>(m, "ObjectColorSource")
    .value("ColorFromLayer", ON::object_color_source::color_from_layer)
    .value("ColorFromObject", ON::object_color_source::color_from_object)
    .value("ColorFromMaterial", ON::object_color_source::color_from_material)
    .value("ColorFromParent", ON::object_color_source::color_from_parent)
    ;

  py::enum_<ON::plot_color_source>(m, "ObjectPlotColorSource")
    .value("PlotColorFromLayer", ON::plot_color_from_layer)
    .value("PlotColorFromObject", ON::plot_color_from_object)
    .value("PlotColorFromDisplay", ON::plot_color_from_display)
    .value("PlotColorFromParent", ON::plot_color_from_parent)
    ;

  py::enum_<ON::plot_weight_source>(m, "ObjectPlotWeightSource")
    .value("PlotWeightFromLayer", ON::plot_weight_from_layer)
    .value("PlotWeightFromObject", ON::plot_weight_from_object)
    .value("PlotWeightFromParent", ON::plot_weight_from_parent)
    ;

  py::enum_<ON::object_linetype_source>(m, "ObjectLinetypeSource")
    .value("LinetypeFromLayer", ON::object_linetype_source::linetype_from_layer)
    .value("LinetypeFromObject", ON::linetype_from_object)
    .value("LinetypeFromParent", ON::linetype_from_parent)
    ;

  py::enum_<ON::object_material_source>(m, "ObjectMaterialSource")
    .value("MaterialFromLayer", ON::material_from_layer)
    .value("MaterialFromObject", ON::material_from_object)
    .value("MaterialFromParent", ON::material_from_parent)
    ;

  py::enum_<ON::object_type>(m, "ObjectType")
    .value("None", ON::unknown_object_type)
    .value("Point", ON::point_object)
    .value("PointSet", ON::pointset_object)
    .value("Curve", ON::curve_object)
    .value("Surface", ON::surface_object)
    .value("Brep", ON::brep_object)
    .value("Mesh", ON::mesh_object)
    .value("Light", ON::light_object)
    .value("Annotation", ON::annotation_object)
    .value("InstanceDefinition", ON::instance_definition)
    .value("InstanceReference", ON::instance_reference)
    .value("TextDot", ON::text_dot)
    .value("Grip", ON::grip_object)
    .value("Detail", ON::detail_object)
    .value("Hatch", ON::hatch_object)
    .value("MorphControl", ON::morph_control_object)
    .value("SubD", ON::subd_object)
    .value("BrepLoop", ON::loop_object)
    .value("PolysrfFilter", ON::polysrf_filter)
    .value("EdgeFilter", ON::edge_filter)
    .value("PolyedgeFilter", ON::polyedge_filter)
    .value("MeshVertex", ON::meshvertex_filter)
    .value("MeshEdge", ON::meshedge_filter)
    .value("MeshFace", ON::meshface_filter)
    .value("Cage", ON::cage_object)
    .value("Phantom", ON::phantom_object)
    .value("ClipPlane", ON::clipplane_object)
    .value("Extrusion", ON::extrusion_object)
    .value("AnyObject", ON::any_object)
    ;

  py::enum_<ON::mesh_type>(m, "MeshType")
    .value("Default", ON::default_mesh)
    .value("Render", ON::render_mesh)
    .value("Analysis", ON::analysis_mesh)
    .value("Preview", ON::preview_mesh)
    .value("Any", ON::any_mesh)
    ;

  py::enum_<ON::object_decoration>(m, "ObjectDecoration")
    .value("None", ON::no_object_decoration)
    .value("StartArrowhead", ON::start_arrowhead)
    .value("EndArrowhead", ON::end_arrowhead)
    .value("BothArrowhead", ON::both_arrowhead)
    ;

  py::enum_<ON::active_space>(m, "ActiveSpace")
    .value("None", ON::active_space::no_space)
    .value("ModelSpace", ON::active_space::model_space)
    .value("PageSpace", ON::active_space::page_space)
    ;

}

pybind11::dict PointToDict(const ON_3dPoint& point)
{
  pybind11::dict rc;
  rc["X"] = point.x;
  rc["Y"] = point.y;
  rc["Z"] = point.z;
  return rc;
}
pybind11::dict VectorToDict(const ON_3dVector& vector)
{
  pybind11::dict rc;
  rc["X"] = vector.x;
  rc["Y"] = vector.y;
  rc["Z"] = vector.z;
  return rc;
}
pybind11::dict PlaneToDict(const ON_Plane& plane)
{
  pybind11::dict rc;
  rc["Origin"] = PointToDict(plane.origin);
  rc["XAxis"] = VectorToDict(plane.xaxis);
  rc["YAxis"] = VectorToDict(plane.yaxis);
  rc["ZAxis"] = VectorToDict(plane.zaxis);
  return rc;
}

ON_3dPoint PointFromDict(pybind11::dict& dict)
{
  ON_3dVector rc;
  rc.x = dict["X"].cast<double>();
  rc.y = dict["Y"].cast<double>();
  rc.z = dict["Z"].cast<double>();
  return rc;
}
ON_3dVector VectorFromDict(pybind11::dict& dict)
{
  ON_3dPoint pt = PointFromDict(dict);
  return ON_3dVector(pt.x, pt.y, pt.z);
}
ON_Plane PlaneFromDict(pybind11::dict& dict)
{
  ON_Plane plane;
  pybind11::dict d = dict["Origin"].cast<pybind11::dict>();
  plane.origin = PointFromDict(d);
  d = dict["XAxis"].cast<pybind11::dict>();
  plane.xaxis = VectorFromDict(d);
  d = dict["YAxis"].cast<pybind11::dict>();
  plane.yaxis = VectorFromDict(d);
  d = dict["ZAxis"].cast<pybind11::dict>();
  plane.zaxis = VectorFromDict(d);
  plane.UpdateEquation();
  return plane;
}

#endif

#if defined(ON_WASM_COMPILE)
using namespace emscripten;

void initDefines(void*)
{
  class_<ON_Line>("Line")
    .constructor<ON_3dPoint, ON_3dPoint>()
    .property("from", &ON_Line::from)
    .property("to", &ON_Line::to)
    .property("length", &ON_Line::Length);


  enum_<ON::object_mode>("ObjectMode")
    .value("Normal", ON::object_mode::normal_object)
    .value("Hidden", ON::object_mode::hidden_object)
    .value("Locked", ON::object_mode::locked_object)
    .value("InstanceDefinitionObject", ON::object_mode::idef_object)
    ;

  enum_<ON::object_color_source>("ObjectColorSource")
    .value("ColorFromLayer", ON::object_color_source::color_from_layer)
    .value("ColorFromObject", ON::object_color_source::color_from_object)
    .value("ColorFromMaterial", ON::object_color_source::color_from_material)
    .value("ColorFromParent", ON::object_color_source::color_from_parent)
    ;

  enum_<ON::plot_color_source>("ObjectPlotColorSource")
    .value("PlotColorFromLayer", ON::plot_color_from_layer)
    .value("PlotColorFromObject", ON::plot_color_from_object)
    .value("PlotColorFromDisplay", ON::plot_color_from_display)
    .value("PlotColorFromParent", ON::plot_color_from_parent)
    ;

  enum_<ON::plot_weight_source>("ObjectPlotWeightSource")
    .value("PlotWeightFromLayer", ON::plot_weight_from_layer)
    .value("PlotWeightFromObject", ON::plot_weight_from_object)
    .value("PlotWeightFromParent", ON::plot_weight_from_parent)
    ;

  enum_<ON::object_linetype_source>("ObjectLinetypeSource")
    .value("LinetypeFromLayer", ON::object_linetype_source::linetype_from_layer)
    .value("LinetypeFromObject", ON::linetype_from_object)
    .value("LinetypeFromParent", ON::linetype_from_parent)
    ;

  enum_<ON::object_material_source>("ObjectMaterialSource")
    .value("MaterialFromLayer", ON::material_from_layer)
    .value("MaterialFromObject", ON::material_from_object)
    .value("MaterialFromParent", ON::material_from_parent)
    ;

  enum_<ON::object_type>("ObjectType")
    .value("None", ON::unknown_object_type)
    .value("Point", ON::point_object)
    .value("PointSet", ON::pointset_object)
    .value("Curve", ON::curve_object)
    .value("Surface", ON::surface_object)
    .value("Brep", ON::brep_object)
    .value("Mesh", ON::mesh_object)
    .value("Light", ON::light_object)
    .value("Annotation", ON::annotation_object)
    .value("InstanceDefinition", ON::instance_definition)
    .value("InstanceReference", ON::instance_reference)
    .value("TextDot", ON::text_dot)
    .value("Grip", ON::grip_object)
    .value("Detail", ON::detail_object)
    .value("Hatch", ON::hatch_object)
    .value("MorphControl", ON::morph_control_object)
    .value("SubD", ON::subd_object)
    .value("BrepLoop", ON::loop_object)
    .value("PolysrfFilter", ON::polysrf_filter)
    .value("EdgeFilter", ON::edge_filter)
    .value("PolyedgeFilter", ON::polyedge_filter)
    .value("MeshVertex", ON::meshvertex_filter)
    .value("MeshEdge", ON::meshedge_filter)
    .value("MeshFace", ON::meshface_filter)
    .value("Cage", ON::cage_object)
    .value("Phantom", ON::phantom_object)
    .value("ClipPlane", ON::clipplane_object)
    .value("Extrusion", ON::extrusion_object)
    .value("AnyObject", ON::any_object)
    ;

  enum_<ON::coordinate_system>("CoordinateSystem")
    .value("World", ON::coordinate_system::world_cs)
    .value("Camera", ON::coordinate_system::camera_cs)
    .value("Clip", ON::coordinate_system::clip_cs)
    .value("Screen", ON::coordinate_system::screen_cs)
    ;

  enum_<ON::mesh_type>("MeshType")
    .value("Default", ON::default_mesh)
    .value("Render", ON::render_mesh)
    .value("Analysis", ON::analysis_mesh)
    .value("Preview", ON::preview_mesh)
    .value("Any", ON::any_mesh)
    ;

  enum_<ON::object_decoration>("ObjectDecoration")
    .value("None", ON::no_object_decoration)
    .value("StartArrowhead", ON::start_arrowhead)
    .value("EndArrowhead", ON::end_arrowhead)
    .value("BothArrowhead", ON::both_arrowhead)
    ;

  enum_<ON::active_space>("ActiveSpace")
    .value("None", ON::active_space::no_space)
    .value("ModelSpace", ON::active_space::model_space)
    .value("PageSpace", ON::active_space::page_space)
    ;
}


emscripten::val PointToDict(const ON_3dPoint& point)
{
  emscripten::val p(emscripten::val::object());
  p.set("X", emscripten::val(point.x));
  p.set("Y", emscripten::val(point.y));
  p.set("Z", emscripten::val(point.z));
  return p;
}
emscripten::val VectorToDict(const ON_3dVector& vector)
{
  emscripten::val p(emscripten::val::object());
  p.set("X", emscripten::val(vector.x));
  p.set("Y", emscripten::val(vector.y));
  p.set("Z", emscripten::val(vector.z));
  return p;
}

emscripten::val PlaneToDict(const ON_Plane& plane)
{
  emscripten::val p(emscripten::val::object());
  p.set("Origin", PointToDict(plane.origin));
  p.set("XAxis", VectorToDict(plane.xaxis));
  p.set("YAxis", VectorToDict(plane.yaxis));
  p.set("ZAxis", VectorToDict(plane.zaxis));
  return p;
}

#endif
