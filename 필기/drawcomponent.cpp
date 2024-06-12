#include "DrawComponent.h"
#include "gl/freeglut.h"
#include "pmp/io/write_obj.h"
#include "pmp/io/io.h"
#include "pmp/algorithms/normals.h"
#include <set>

void DrawComponent::Init()
{
    InitMyMesh();
    // compute normals
    pmp::vertex_normals(mesh);

    pmp::write(mesh, "hm11.obj");
}

void DrawComponent::InitLoadFile()
{
    pmp::read(mesh, "obj\\kitten.obj");
    pmp::vertex_normals(mesh);
}

void DrawComponent::InitMyMesh()
{
    // Add 8 vertices for a cube
    const auto v0 = mesh.add_vertex(pmp::Point(0, 0, 0));
    const auto v1 = mesh.add_vertex(pmp::Point(1, 0, 0));
    const auto v2 = mesh.add_vertex(pmp::Point(1, 1, 0));
    const auto v3 = mesh.add_vertex(pmp::Point(0, 1, 0));
    const auto v4 = mesh.add_vertex(pmp::Point(0, 0, 1));
    const auto v5 = mesh.add_vertex(pmp::Point(1, 0, 1));
    const auto v6 = mesh.add_vertex(pmp::Point(1, 1, 1));
    const auto v7 = mesh.add_vertex(pmp::Point(0, 1, 1));

    // Add 6 faces for the cube
    mesh.add_triangle(v0, v1, v2);
    mesh.add_triangle(v0, v2, v3);

    mesh.add_triangle(v1, v5, v6);
    mesh.add_triangle(v1, v6, v2);

    mesh.add_triangle(v5, v4, v7);
    mesh.add_triangle(v5, v7, v6);

    mesh.add_triangle(v4, v0, v3);
    mesh.add_triangle(v4, v3, v7);

    mesh.add_triangle(v3, v2, v6);
    mesh.add_triangle(v3, v6, v7);

    mesh.add_triangle(v4, v5, v1);
    mesh.add_triangle(v4, v1, v0);

    std::cout << "vertices: " << mesh.n_vertices() << std::endl;
    std::cout << "edges: " << mesh.n_edges() << std::endl;
    std::cout << "faces: " << mesh.n_faces() << std::endl;
}

std::set<pmp::Face> get_ring_faces(const pmp::SurfaceMesh& mesh, const std::set<pmp::Face>& prev_ring) {
    std::set<pmp::Face> ring_faces;
    for (const auto& f : prev_ring) {
        for (const auto& v : mesh.vertices(f)) {
            for (const auto& ff : mesh.faces(v)) {
                if (prev_ring.find(ff) == prev_ring.end()) {
                    ring_faces.insert(ff);
                }
            }
        }
    }
    return ring_faces;
}

void DrawComponent::Draw()
{
    auto n = mesh.get_vertex_property<pmp::Normal>("v:normal");

    std::set<pmp::Face> ring0;
    ring0.insert(*mesh.faces().begin());

    std::set<pmp::Face> ring1 = get_ring_faces(mesh, ring0);
    std::set<pmp::Face> ring2 = get_ring_faces(mesh, ring1);
    std::set<pmp::Face> ring3 = get_ring_faces(mesh, ring2);
    std::set<pmp::Face> ring4 = get_ring_faces(mesh, ring3);

    for (auto f : mesh.faces()) {
        if (ring0.find(f) != ring0.end()) {
            glColor3f(1.0, 0.0, 0.0); // Red for 0-ring faces
        }
        else if (ring1.find(f) != ring1.end()) {
            glColor3f(0.0, 0.0, 1.0); // Blue for 1-ring faces
        }
        else if (ring2.find(f) != ring2.end()) {
            glColor3f(1.0, 1.0, 0.0); // Yellow for 2-ring faces
        }
        else if (ring3.find(f) != ring3.end()) {
            glColor3f(0.0, 1.0, 0.0); // Green for 3-ring faces
        }
        else if (ring4.find(f) != ring4.end()) {
            glColor3f(1.0, 0.0, 1.0); // Purple for 4-ring faces
        }
        else {
            glColor3f(0.5, 0.5, 0.5); // Default color for others
        }

        glBegin(GL_TRIANGLES);
        for (auto v : mesh.vertices(f)) {
            auto p = mesh.position(v);
            glNormal3dv(n[v].data());
            glVertex3dv(p.data());
        }
        glEnd();
    }
}