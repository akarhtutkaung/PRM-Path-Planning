# Voronoi Path Planning
This program has been remodified into English wording from the original version.

Original version: https://github.com/SimoneTinella/Path-Planning-Robot-over-Voronoi-Diagram

## Summary
This program will generate the path (nodes) of voronoi edges by getting the user starting position and ending position. Then user can use Matlab to generate the image of the paths.

## Prerequisite
- Make
- g++
- Matlab

## Usage Instruction
1. Inside the root(repo) folder, compile the codes.
    ```
    make
    ```
    *Note: This will create a build folder*
2. Go inside the `build` folder
    ```
    cd build
    ```
3. Run the program
    ```
    ./Voronoi
    ```
    *Note: This will generate the path/nodes*
4. To visualize the path, open current `build` folder in Matlab and run either `drawAll.m` or `drawPathOnly.m` file. 

## Modifying the environment
The environment is hard coded, thus, to change the environment, set the data inside the `src/Main.ccp`.

Declaring Obstacle Example:
  ```
  std::vector<Obstacle *> obstacles;
  Obstacle *rectangleObstacle;
  // Verticies should be declare in clockwise position
  std::vector<Point *> rectangleObstaclePts;
  rectangleObstaclePts.push_back(new Point(20, 80)); // Left Bottom
  rectangleObstaclePts.push_back(new Point(20, 90)); // Left Top
  rectangleObstaclePts.push_back(new Point(30, 90)); // Right Top
  rectangleObstaclePts.push_back(new Point(30, 80)); // Right Bottom
  rectangleObstacle = new Obstacle(&rectangleObstaclePts);
  obstacles.push_back(rectangleObstacle);
  ```

Declaring Map Area:
  ```
  const double maxX = ?;
  const double maxY = ?;
  ```

## Example Generated Path

Border Red: Borders <br>
Green Line: Generated Path using Voronoi <br>
Inner Red Rectangles: Obstacles <br>
Inner Red Dots: Junctions <br>
Yellow dots/line: chosen path to go from starting to goal <br>
![voronoi_example](https://user-images.githubusercontent.com/76828992/201459516-c200127f-8e61-42cd-8f40-182761ac9efa.PNG)

![voronoi_example_path_only](https://user-images.githubusercontent.com/76828992/201459845-263a8816-3140-4ff6-9043-ba1dfdb3ad03.png)

