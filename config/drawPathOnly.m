load('obstacles.txt')
load('pathsToFollow.txt')
hold on
plot(obstacles(:,1),obstacles(:,2),'r.','MarkerSize',10)
plot(pathsToFollow(:,1),pathsToFollow(:,2),'MarkerEdgeColor','y','LineWidth',3)
plot(pathsToFollow(:,1),pathsToFollow(:,2),'r.','MarkerSize',15,'MarkerEdgeColor','y')
hold off