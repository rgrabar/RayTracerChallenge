## Build
Clone the raylib repo (https://github.com/raysan5/raylib) inside this project folder. Don't forget to install the required libraries e.g for ubuntu 
`sudo apt install libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev` (more details https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux) on windows it should work without this step.
After that you can run one of the build files. 
This should build raylib and the project itself. Can also be built by using Visual Studio and raylib as a NuGet package (Tools -> NuGet Package Manager).

## Build Tests
### Linux
Install gtests: `sudo apt-get install libgtest-dev`.
<br>
Build by using one of the build files.

### Windows 
Add google tests by using NuGet and build the solution.
<br>
***Note:*** The test name should be changed, it's a bit annoying to do tho. 


## Scenes

***Note:*** first three scenes won't be previewd using raylib, however every scene gets saved as canvas.ppm. 


<details>
  <summary>Projectile</summary>
  
  Command: ```RayTracer Projectile```
  
  ![image](https://user-images.githubusercontent.com/78257998/230852865-829d25bf-e463-46ed-a213-609c1eabcff9.png)
</details>

<details>
  <summary>Clock</summary>
  
  Command: ```RayTracer Clock```
  
  ![image](https://user-images.githubusercontent.com/78257998/230853858-5dc740b8-a91d-42f4-a154-132e0805e35b.png)
</details>

<details>
  <summary>RedCircle</summary>
  
  Command: ```RayTracer RedCircle```
  
  ![image](https://user-images.githubusercontent.com/78257998/230853994-e875de13-427a-4979-b3e7-578b7e74e063.png)
</details>

<details>
  <summary>Shadows</summary>
  
  Command: ```RayTracer Shadows```
  
  ![image](https://user-images.githubusercontent.com/78257998/230854165-0f42af14-ed66-407a-9f3f-0665ffa08388.png)
</details>

<details>
  <summary>BadSmiley</summary>
  
  Command: ```RayTracer BadSmiley```
  
  ![image](https://user-images.githubusercontent.com/78257998/230854332-ccfd9ed7-1b3b-4597-bbe5-f9d1d95b897a.png)
</details>


<details>
  <summary>RefractiveSphere</summary>
  
  Command: ```RayTracer RefractiveSphere --aliasing 16```
  
  ![image](https://user-images.githubusercontent.com/78257998/230879547-0e0e70e8-15ff-44cf-84f9-111f44ca5f31.png)
</details>

<details>
  <summary>AllShapes</summary>
  
  Command: ```RayTracer AllShapes```
  
  ![image](https://user-images.githubusercontent.com/78257998/230855228-2faa8a71-36d4-4356-a287-212e72c55dd0.png)
</details>

<details>
  <summary>Hexagon</summary>
  
  Command: ```RayTracer Hexagon```
  
  ![image](https://user-images.githubusercontent.com/78257998/230855337-3bded9a0-45d4-4113-8f0d-f1fd5290bdf5.png)
</details>

<details>
  <summary>Spheres</summary>
  
  Command: ```RayTracer Spheres```
  <br>
  ***Note:*** You can also try the same scene, Command: ```RayTracer SpheresDivide``` to compare the speed when BVH is enabled.
  
  ![image](https://user-images.githubusercontent.com/78257998/230855483-84cc41dd-723a-4664-86e6-cf13a4eb5641.png)
</details>

<details>
  <summary>Teapot</summary>
  
  Both teapot .objs can be found here: https://graphics.cs.utah.edu/courses/cs6620/fall2013/prj05/
  
  Command: ```RayTracer Teapot```
  
  ![image](https://user-images.githubusercontent.com/78257998/230855637-fbb52dda-7eff-4e8f-94b5-1a12ba163511.png)
  
  Same teapot but now using the normals to get a smoother look.
  
   Command: ```RayTracer LoadOBJ --path assets/smoothTriangles.obj```
   <br>
   ***Note:*** LoadOBJ takes path to the OBJ file that will be rendered, however sometimes it needs to be adjusted to be in the centre of the scene. For this example the transform was ``` translate(1, -1, -40) * scale(20, 20, 20) * rotationX(-TEST_PI / 2);```
  
  ![image](https://user-images.githubusercontent.com/78257998/230880426-81844dd9-3cf5-4ccd-aa79-ed1518856f03.png)

</details>

<details>
  <summary>CS</summary>
  
  CS:GO knife obj from: https://www.dropbox.com/s/5shafyy1rmnwelw/Knife%20resources.zip?dl=0&file_subpath=%2FKnife+resources%2FModels
  
  Command: ```RayTracer CS```
  
  ![image](https://user-images.githubusercontent.com/78257998/230855795-c7a14f50-58c9-4c4d-92a1-01919b027b82.png)
</details>

<details>
  <summary>Dragon</summary>
  
  Dragon obj from: http://www.raytracerchallenge.com/bonus/bounding-boxes.html
  
  Command: ```RayTracer Dragon```
  
  ![image](https://user-images.githubusercontent.com/78257998/230856381-314584e8-df48-425d-9493-414747554ddc.png)
</details>

<details>
  <summary>Astronaut</summary>
  
  Astronaut obj from: https://nasa3d.arc.nasa.gov/models
  
  Command: ```RayTracer Astronaut```
  
  ![image](https://user-images.githubusercontent.com/78257998/230856626-a1c99304-2770-4747-8632-3f5f60498626.png)
</details>

<details>
  <summary>CSG</summary>
  
  Command: ```RayTracer CSG```
  
  ![image](https://user-images.githubusercontent.com/78257998/230870710-c3f63827-138d-4f7a-aa6f-1088910d8364.png)
</details>

<details>
  <summary>AreaLight</summary>
  
  Command: ```RayTracer AreaLight```
  
  ![image](https://user-images.githubusercontent.com/78257998/230873100-317066aa-355c-4e48-bd76-71edff666a39.png)
</details>

<details>
  <summary>SpotLight</summary>
  
  Command: ```RayTracer SpotLight```
  
  ![image](https://user-images.githubusercontent.com/78257998/230873685-51f79041-daf1-4d3e-b3e4-aec516737aee.png)
</details>


<details>
  <summary>Aliasing</summary>
  No antialiasing
  
  Command: ```RayTracer Aliasing```
  
  ![image](https://user-images.githubusercontent.com/78257998/230873831-482c0015-2282-4e24-98bf-3bec315ee907.png)
  
  
  Edge preveiw
  
   Command: ```RayTracer Aliasing --aliasing 16 --highlights 1```
  
  ![image](https://user-images.githubusercontent.com/78257998/230874465-d8196771-3d9b-41c6-9c27-2afa07500564.png)
  
  Antialiasing only the detected edges
  
  Command: ```RayTracer Aliasing --aliasing 16 --edge 1```
  
  ![image](https://user-images.githubusercontent.com/78257998/230874832-626db5cc-b7b3-442f-8ff5-c0dfa5c59a7e.png)

  Command: ```RayTracer Aliasing --aliasing 16```
  
  Antialiasing the whole image, 16x
  ![image](https://user-images.githubusercontent.com/78257998/230874403-ccde5620-4580-4696-a2e2-d3ecd4394511.png)

</details>

<details>
  <summary>CubeTest</summary>
  
  Command: ```RayTracer CubeTest```
  
  ![image](https://user-images.githubusercontent.com/78257998/230875278-fe69ff8c-64c8-4a15-9f74-a6715350d1df.png)
</details>

<details>
  <summary>Earth</summary>
  
  Earth texture from: http://planetpixelemporium.com/earth.html
  <br>
  ***Note:*** textures need to be in P3 or p6 format.
  
  Command: ```RayTracer Earth```
  
  ![image](https://user-images.githubusercontent.com/78257998/230875635-9ff58811-4147-43fc-bf10-51f9f0e25a28.png)
</details>

