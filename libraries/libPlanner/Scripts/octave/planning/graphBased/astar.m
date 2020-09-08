%% https://en.wikipedia.org/wiki/A*_search_algorithm
function cost = heuristicCost(pos)
    cost =0;
end

function found = astar(map, startPos, goalPos)
    % implemented as a priority queue usually
    openSet = {startPos}; 
    cameFrom= {};
    gScore = inf(size(map));
    gScore(startPos) = 0;
    fScore = inf(size(map));
    fScore(startPos) = heuristicCost(startPos);% + gScore(startPos) =0

    found = false;
    path = [];
    while (~isempty(openSet))
       [colmin, colIndex]= min(min(fscore)); 
       [minVal, rowIndex] = min(fScore(:,colIndex));

       current = [rowIndex, colIndex];
       if (norm(current - goal)<0.01)
           return reconstructPath(cameFrom, current);
       end
       openSet
    end

end

clear all;
% generate a map
map = zeros(100,100);
startPos = [1,1];
goalPos = [100,100];
found = astar(map, startPos, goalPos);



