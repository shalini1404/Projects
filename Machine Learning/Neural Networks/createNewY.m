function Y_new=createNewY(Ytrain)
    win_ind = find(Ytrain==1);                                      %win index
    lose_ind = find(Ytrain==2);                                     %lose index
    draw_ind = find(Ytrain==3);                                     %draw index
    Y_new = zeros(size(Ytrain,1),3); 
    %update y by replacing each output with 3 binary bits
    Y_new(win_ind,:) = repmat([1,0,0],length(win_ind),1);
    Y_new(lose_ind,:) = repmat([0,1,0],length(lose_ind),1);
    Y_new(draw_ind,:) = repmat([0,0,1],length(draw_ind),1);