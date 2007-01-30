// ***************************************************************************
//
//   Generated automatically by genwrapper.
//   Please DO NOT EDIT this file!
//
// ***************************************************************************

#include <osgIntrospection/ReflectionMacros>
#include <osgIntrospection/TypedMethodInfo>
#include <osgIntrospection/StaticMethodInfo>
#include <osgIntrospection/Attributes>

#include <osg/Referenced>
#include <osg/State>
#include <osg/StateSet>
#include <osgUtil/RenderLeaf>
#include <osgUtil/StateGraph>

// Must undefine IN and OUT macros defined in Windows headers
#ifdef IN
#undef IN
#endif
#ifdef OUT
#undef OUT
#endif

BEGIN_VALUE_REFLECTOR(osgUtil::LessDepthSortFunctor)
	I_Constructor0(____LessDepthSortFunctor,
	               "",
	               "");
END_REFLECTOR

TYPE_NAME_ALIAS(std::map< const osg::StateSet * COMMA  osg::ref_ptr< osgUtil::StateGraph > >, osgUtil::StateGraph::ChildList);

TYPE_NAME_ALIAS(std::vector< osg::ref_ptr< osgUtil::RenderLeaf > >, osgUtil::StateGraph::LeafList);

BEGIN_OBJECT_REFLECTOR(osgUtil::StateGraph)
	I_BaseType(osg::Referenced);
	I_Constructor0(____StateGraph,
	               "",
	               "");
	I_Constructor2(IN, osgUtil::StateGraph *, parent, IN, const osg::StateSet *, stateset,
	               ____StateGraph__StateGraph_P1__C5_osg_StateSet_P1,
	               "",
	               "");
	I_Method0(osgUtil::StateGraph *, cloneType,
	          __StateGraph_P1__cloneType,
	          "",
	          "");
	I_Method1(void, setUserData, IN, osg::Referenced *, obj,
	          __void__setUserData__osg_Referenced_P1,
	          "",
	          "");
	I_Method0(osg::Referenced *, getUserData,
	          __osg_Referenced_P1__getUserData,
	          "",
	          "");
	I_Method0(const osg::Referenced *, getUserData,
	          __C5_osg_Referenced_P1__getUserData,
	          "",
	          "");
	I_Method0(bool, empty,
	          __bool__empty,
	          "return true if all of drawables, lights and children are empty. ",
	          "");
	I_Method0(bool, leaves_empty,
	          __bool__leaves_empty,
	          "",
	          "");
	I_Method0(float, getAverageDistance,
	          __float__getAverageDistance,
	          "",
	          "");
	I_Method0(float, getMinimumDistance,
	          __float__getMinimumDistance,
	          "",
	          "");
	I_Method0(void, sortFrontToBack,
	          __void__sortFrontToBack,
	          "",
	          "");
	I_Method0(void, reset,
	          __void__reset,
	          "Reset the internal contents of a StateGraph, including deleting all children. ",
	          "");
	I_Method0(void, clean,
	          __void__clean,
	          "Recursively clean the StateGraph of all its drawables, lights and depths. ",
	          "Leaves children intact, and ready to be populated again. ");
	I_Method0(void, prune,
	          __void__prune,
	          "Recursively prune the StateGraph of empty children. ",
	          "");
	I_Method1(osgUtil::StateGraph *, find_or_insert, IN, const osg::StateSet *, stateset,
	          __StateGraph_P1__find_or_insert__C5_osg_StateSet_P1,
	          "",
	          "");
	I_Method1(void, addLeaf, IN, osgUtil::RenderLeaf *, leaf,
	          __void__addLeaf__RenderLeaf_P1,
	          "add a render leaf. ",
	          "");
	I_StaticMethod3(void, moveStateGraph, IN, osg::State &, state, IN, osgUtil::StateGraph *, sg_curr, IN, osgUtil::StateGraph *, sg_new,
	                __void__moveStateGraph__osg_State_R1__StateGraph_P1__StateGraph_P1_S,
	                "",
	                "");
	I_StaticMethod2(void, moveToRootStateGraph, IN, osg::State &, state, IN, osgUtil::StateGraph *, sg_curr,
	                __void__moveToRootStateGraph__osg_State_R1__StateGraph_P1_S,
	                "",
	                "");
	I_SimpleProperty(float, AverageDistance, 
	                 __float__getAverageDistance, 
	                 0);
	I_SimpleProperty(float, MinimumDistance, 
	                 __float__getMinimumDistance, 
	                 0);
	I_SimpleProperty(osg::Referenced *, UserData, 
	                 __osg_Referenced_P1__getUserData, 
	                 __void__setUserData__osg_Referenced_P1);
	I_PublicMemberProperty(osgUtil::StateGraph *, _parent);
	I_PublicMemberProperty(int, _depth);
	I_PublicMemberProperty(osgUtil::StateGraph::ChildList, _children);
	I_PublicMemberProperty(osgUtil::StateGraph::LeafList, _leaves);
	I_PublicMemberProperty(float, _averageDistance);
	I_PublicMemberProperty(float, _minimumDistance);
	I_PublicMemberProperty(osg::ref_ptr< osg::Referenced >, _userData);
	I_PublicMemberProperty(bool, _dynamic);
END_REFLECTOR

BEGIN_VALUE_REFLECTOR(osg::ref_ptr< osgUtil::RenderLeaf >)
	I_Constructor0(____ref_ptr,
	               "",
	               "");
	I_Constructor1(IN, osgUtil::RenderLeaf *, ptr,
	               ____ref_ptr__T_P1,
	               "",
	               "");
	I_Constructor1(IN, const osg::ref_ptr< osgUtil::RenderLeaf > &, rp,
	               ____ref_ptr__C5_ref_ptr_R1,
	               "",
	               "");
	I_Method0(osgUtil::RenderLeaf *, get,
	          __T_P1__get,
	          "",
	          "");
	I_Method0(bool, valid,
	          __bool__valid,
	          "",
	          "");
	I_Method0(osgUtil::RenderLeaf *, release,
	          __T_P1__release,
	          "",
	          "");
	I_Method1(void, swap, IN, osg::ref_ptr< osgUtil::RenderLeaf > &, rp,
	          __void__swap__ref_ptr_R1,
	          "",
	          "");
	I_SimpleProperty(osgUtil::RenderLeaf *, , 
	                 __T_P1__get, 
	                 0);
END_REFLECTOR

BEGIN_VALUE_REFLECTOR(osg::ref_ptr< osgUtil::StateGraph >)
	I_Constructor0(____ref_ptr,
	               "",
	               "");
	I_Constructor1(IN, osgUtil::StateGraph *, ptr,
	               ____ref_ptr__T_P1,
	               "",
	               "");
	I_Constructor1(IN, const osg::ref_ptr< osgUtil::StateGraph > &, rp,
	               ____ref_ptr__C5_ref_ptr_R1,
	               "",
	               "");
	I_Method0(osgUtil::StateGraph *, get,
	          __T_P1__get,
	          "",
	          "");
	I_Method0(bool, valid,
	          __bool__valid,
	          "",
	          "");
	I_Method0(osgUtil::StateGraph *, release,
	          __T_P1__release,
	          "",
	          "");
	I_Method1(void, swap, IN, osg::ref_ptr< osgUtil::StateGraph > &, rp,
	          __void__swap__ref_ptr_R1,
	          "",
	          "");
	I_SimpleProperty(osgUtil::StateGraph *, , 
	                 __T_P1__get, 
	                 0);
END_REFLECTOR

STD_MAP_REFLECTOR(std::map< const osg::StateSet * COMMA  osg::ref_ptr< osgUtil::StateGraph > >);

STD_VECTOR_REFLECTOR(std::vector< osg::ref_ptr< osgUtil::RenderLeaf > >);

