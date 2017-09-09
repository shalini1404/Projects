function [J_theta,out_o] = calcost(hid_theta,Xtrain,out_theta,Y_new)
m = size(Xtrain,1);
onerow = ones(1,size(Xtrain,1));
hid_o_tmp = sigmf(hid_theta * Xtrain',[1 0]);               %change to i here---->output from hidden layer
hid_o = [onerow;hid_o_tmp];
out_o = sigmf(out_theta * hid_o,[1 0]);
J_theta = Y_new'-out_o;                              %change to i here
J_theta = sum(sum(J_theta.*J_theta))/(2*m);