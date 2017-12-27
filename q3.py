import h5py
import vtk

f = h5py.File("particles.h5","r")   # Read in the file "particles.h5"
dataset = f["particle data"]    # Access the dataset "particle data" in "particles.h5"
points = vtk.vtkPoints()
points.SetNumberOfPoints(dataset.shape[0]) # Create a list of points for particle locations
for idx, item in enumerate(dataset):
    points.SetPoint(idx,dataset[idx][0],dataset[idx][1],dataset[idx][2])

lines = vtk.vtkCellArray()
lines.InsertNextCell(dataset.shape[0])
for idx in range(0,dataset.shape[0]):   # Assign the connectivity between the points
    lines.InsertCellPoint(idx)

polygon = vtk.vtkPolyData() # Create a polygon geometric structure
polygon.SetPoints(points)
polygon.SetLines(lines)

polygonMapper = vtk.vtkPolyDataMapper() # Map the polygonal data of graphics
polygonMapper.SetInputData(polygon)
polygonMapper.Update()

axes = vtk.vtkAxesActor()   # Create some axes
polygonActor = vtk.vtkActor()   # Manage the rendering of the mapping
polygonActor.SetMapper(polygonMapper)
renderer = vtk.vtkRenderer()    # The viewport on the screen
renderer.AddActor(polygonActor)
renderer.AddActor(axes)
renderer.SetBackground(0.1,0.2,0.3)

renderer.ResetCamera()

# Start rendering the window
renderWindow = vtk.vtkRenderWindow()
renderWindow.AddRenderer(renderer)

# Set Interactor
renderWindowInteractor = vtk.vtkRenderWindowInteractor()
renderWindowInteractor.SetRenderWindow(renderWindow)

# Begin Interaction
renderWindow.Render()
renderWindow.SetWindowName("Data Viewer")
renderWindowInteractor.Start()
