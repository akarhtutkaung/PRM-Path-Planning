load('obstacles.txt')
load('randomNodes.txt')
hold on
plot(obstacles(:,1),obstacles(:,2),'g.','MarkerSize',10)
plot(randomNodes(:,1),randomNodes(:,2),'r.','MarkerSize',5,'MarkerEdgeColor','r')
hold off