# PRM Path Planning 

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
    ./RandomPath
    ```
    *Note: This will generate the path*
4. To visualize the path, open current `build` folder in Matlab and run either `drawAll.m` or `drawPathOnly.m` file. 

## Modifying the environment
The environment is hard coded, thus, to change the environment, set the data inside the `src/Main.ccp`.

Declaring Obstacle Example:
  ```
  std::vector<Obstacle *> obstacles;
  Obstacle *rectangleObstacle;
  // Verticies should be declare in clockwise position
  std::vector<Vector2 *> rectangleObstaclePts;
  rectangleObstaclePts.push_back(new Vector2(20, 80)); // Left Bottom
  rectangleObstaclePts.push_back(new Vector2(20, 90)); // Left Top
  rectangleObstaclePts.push_back(new Vector2(30, 90)); // Right Top
  rectangleObstaclePts.push_back(new Vector2(30, 80)); // Right Bottom
  rectangleObstacle = new Obstacle(&rectangleObstaclePts);
  obstacles.push_back(rectangleObstacle);
  ```

Declaring Map Area:
  ```
  const double maxX = ?;
  const double maxY = ?;
  ```

## Example Generated Path


