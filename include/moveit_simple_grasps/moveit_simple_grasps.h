#ifndef MOVEIT_SIMPLE_GRASPS_H
#define MOVEIT_SIMPLE_GRASPS_H

#include "moveit_simple_grasps/simple_grasps.h"
#include <moveit_msgs/CollisionObject.h>

namespace moveit_simple_grasps
{

// TODO
//
// Then: see how to generalize everything (i.e. where to get/store pose to shape tfs etc)
// Might be able to get from extends even when have mesh if we know the primitive
// -> in a way they fit to these grasps
// Can use that as offset already
// Or external??? Because now they fit...
// Or does it depend where we get the info from?
// i.e. mesh + IS shape x -> extents from mesh/pcl/etc not from shape!
// -> Then it gets interesting
//
// With DB conn really check what our full iface is in terms of input data
// mesh/pcl + IS shape -> grasps that fit mesh?
// maybe with wrapper in between to leave SimpleGrasps alone/simple.

/// Generate Simple Grasps for moveit CollisionObjects.
class MoveitSimpleGrasps
{
    public:
        MoveitSimpleGrasps(moveit_visual_tools::VisualToolsPtr rviz_tools = moveit_visual_tools::VisualToolsPtr());

        /// Generate grasps for a CollisionObject.
        /**
         * The CollisionObject already contains header and poses for its individual components.
         * Grasps are generated for all usable components, i.e. all SolidPrimitives and Meshes.
         * Grasps for each SolidPrimitive are generated directly from SimpleGrasps.
         * For the Meshes mesh_shape_types indicates, which shape type each mesh in meshes can be matched to.
         * These must be given and it is assumed that meshes are already aligned, e.g. a box mesh
         * is an axis aligned bounding box, a cylinder stands up right, etc.
         *
         * \param [in] mesh_shape_types shape types for each mesh according to shape_msgs/SolidPrimitive
         */
        bool generateShapeGrasps(const moveit_msgs::CollisionObject & co, const GraspData & grasp_data,
                const std::vector<unsigned char> & mesh_shape_types,
                std::vector<moveit_msgs::Grasp> & possible_grasps);

    protected:
        /// Create a primitive shape with shape_type at shape_pose that best overlays the mesh at mesh_pose.
        /// It is assumed that both are already aligned, i.e. no matching or checking is performed,
        bool createPrimitiveFromMesh(const shape_msgs::Mesh & mesh, const geometry_msgs::Pose & mesh_pose,
                unsigned char shape_type, shape_msgs::SolidPrimitive & shape, geometry_msgs::Pose & shape_pose);

    protected:
        SimpleGraspsPtr simple_grasps_;
};

}

#endif

