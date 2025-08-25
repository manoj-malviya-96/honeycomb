#include "vtk_renderer.h"
#include <vtkActor.h>
#include <vtkCellArray.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkLine.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTubeFilter.h>
#include "skeleton_2d.h"

namespace HoneyComb::Renderer {

namespace {
vtkSmartPointer<vtkPoints> makePoints(const std::vector<Frame::Vertex>& vertices) {
    auto points = vtkSmartPointer<vtkPoints>::New();
    for (const auto& v : vertices) {
        points->InsertNextPoint(v.x, v.y, 0.0);
    }
    return points;
}

vtkSmartPointer<vtkCellArray> makeLines(const std::unordered_set<Frame::Edge, Frame::EdgeHasher>& edges) {
    auto lines = vtkSmartPointer<vtkCellArray>::New();
    for (const auto& e : edges) {
        auto line = vtkSmartPointer<vtkLine>::New();
        line->GetPointIds()->SetId(0, e.start);
        line->GetPointIds()->SetId(1, e.end);
        lines->InsertNextCell(line);
    }
    return lines;
}

vtkSmartPointer<vtkPolyData> makePolygon(const Frame::Skeleton2D& skeleton2d) {
    const auto polyData = vtkSmartPointer<vtkPolyData>::New();
    polyData->SetPoints(makePoints(skeleton2d.getVertices()));
    polyData->SetLines(makeLines(skeleton2d.getEdges()));
    return polyData;
}

vtkSmartPointer<vtkTubeFilter> extrudePolygon(const vtkSmartPointer<vtkPolyData> polyData) {
    auto result = vtkSmartPointer<vtkTubeFilter>::New();
    result->SetInputData(polyData);
    result->SetRadius(0.1);
    result->SetNumberOfSides(4);
    result->CappingOn();
    result->Update();
    return result;
};


constexpr int SCREEN_WIDTH = 1200;
constexpr int SCREEN_HEIGHT = 720;
constexpr double BG_COLOR = 0.1; // 0.1 in all RGB channels

} // namespace


void renderSkeleton(const Frame::Skeleton2D& skeleton2d) {
    const auto polygon = makePolygon(skeleton2d);
    const auto extrudedMesh = extrudePolygon(polygon);

    const auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(extrudedMesh->GetOutputPort());

    const auto actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    const auto renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->SetBackground(BG_COLOR, BG_COLOR, BG_COLOR);

    const auto window = vtkSmartPointer<vtkRenderWindow>::New();
    window->AddRenderer(renderer);
    window->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    const auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(window);
    const auto style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    interactor->SetInteractorStyle(style);

    window->Render();
    interactor->Start();
}

} // namespace HoneyComb::Renderer
