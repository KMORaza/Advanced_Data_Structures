#include <iostream>
#include <vector>
class HalfEdge;
class Face;
class Vertex;
class HalfEdge {
public:
    Vertex* origin;    
    HalfEdge* twin;     
    Face* incidentFace; 
    HalfEdge* next; 
    HalfEdge* prev;     
    HalfEdge(Vertex* o, Face* f) : origin(o), twin(nullptr), incidentFace(f), next(nullptr), prev(nullptr) {}
};
class Face {
public:
    HalfEdge* outerComponent; 
    int id;                   
    Face() : outerComponent(nullptr), id(-1) {}
};
class Vertex {
public:
    double x, y;
    HalfEdge* incidentEdge;
    Vertex(double xCoord, double yCoord) : x(xCoord), y(yCoord), incidentEdge(nullptr) {}
};
class DCEL {
public:
    std::vector<HalfEdge> halfEdges;
    std::vector<Face> faces;
    std::vector<Vertex> vertices;
    DCEL() {}
    ~DCEL() {}
    Vertex* addVertex(double x, double y) {
        vertices.emplace_back(x, y);
        return &vertices.back();
    }
    Face* addFace() {
        faces.emplace_back();
        return &faces.back();
    }
    HalfEdge* addHalfEdge(Vertex* origin, Face* incidentFace) {
        halfEdges.emplace_back(origin, incidentFace);
        return &halfEdges.back();
    }
};
int main() {
    DCEL dcel;
    Vertex* v1 = dcel.addVertex(0.0, 0.0);
    Vertex* v2 = dcel.addVertex(1.0, 0.0);
    Vertex* v3 = dcel.addVertex(1.0, 1.0);
    Vertex* v4 = dcel.addVertex(0.0, 1.0);
    Face* face1 = dcel.addFace();
    Face* face2 = dcel.addFace();
    HalfEdge* he1 = dcel.addHalfEdge(v1, face1);
    HalfEdge* he2 = dcel.addHalfEdge(v2, face1);
    HalfEdge* he3 = dcel.addHalfEdge(v3, face1);
    HalfEdge* he4 = dcel.addHalfEdge(v4, face2);
    HalfEdge* he5 = dcel.addHalfEdge(v1, face2);
    HalfEdge* he6 = dcel.addHalfEdge(v3, face2);
    he1->twin = he2;
    he2->twin = he3;
    he3->twin = he1;
    he4->twin = he5;
    he5->twin = he6;
    he6->twin = he4;
    he1->next = he2;
    he2->next = he3;
    he3->next = he1;
    he1->prev = he3;
    he2->prev = he1;
    he3->prev = he2;
    face1->outerComponent = he1;
    he4->next = he5;
    he5->next = he6;
    he6->next = he4;
    he4->prev = he6;
    he5->prev = he4;
    he6->prev = he5;
    face2->outerComponent = he4;
    std::cout << "Vertices: " << dcel.vertices.size() << "\n";
    std::cout << "Half-Edges: " << dcel.halfEdges.size() << "\n";
    std::cout << "Faces: " << dcel.faces.size() << "\n";
    return 0;
}
