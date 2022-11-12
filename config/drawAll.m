load('obstacles.txt')
load('randomPaths.txt')
load('pathsToFollow.txt')
plot(randomPaths(:,1),randomPaths(:,2),'r.','MarkerSize',10,'MarkerEdgeColor','g')
hold on
plot(obstacles(:,1),obstacles(:,2),'r.','MarkerSize',10)
plot(pathsToFollow(:,1),pathsToFollow(:,2),'MarkerEdgeColor','y','LineWidth',3)
plot(pathsToFollow(:,1),pathsToFollow(:,2),'r.','MarkerSize',15,'MarkerEdgeColor','y')
hold off