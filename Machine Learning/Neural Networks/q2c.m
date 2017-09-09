tic
%---------------data import-----------------------------------------

Xtrain = importdata('connect_4\train.data', ',');               %read text file of train data
Ytrain =  Xtrain(:,(size(Xtrain,2)));                           %store labels in ytrain  
Xtest = importdata('connect_4\test.data', ',');               %read text file of train data
m2 = size(Xtest,1);
Ytest =  Xtest(:,(size(Xtest,2)));                           %store labels in ytrain                        
Xtest = [ones(m2,1) Xtest];                            %ones column added to training x data
Xtest = Xtest(:,1:(size(Xtest,2)-1));
Y_new = createNewY(Ytrain);
m = size(Xtrain,1);                                                  %total number no of training examples
Xtrain = [ones(m,1) Xtrain];                            %ones column added to training x data
Xtrain = Xtrain(:,1:(size(Xtrain,2)-1));                %last column removed from training data

%-----------------------theta initialize---------------------------------------

hid_layer = 50:50:500;
eeta = 0.1;
accuracy_train = zeros(1,size(hid_layer,2));
accuracy_test = zeros(1,size(hid_layer,2));
for j=1:size(hid_layer,2)
    hid_theta = ((1+1).*rand(hid_layer(j),127) - 1)/1000;            %initialize theta near zero for each units in hidden layer layer
    out_theta = ((1+1).*rand(3,hid_layer(j)+1) - 1)/1000;              %initialize theta near zero for each unit in output layer
    [J_theta,final_out] = calcost(hid_theta,Xtrain,out_theta,Y_new);
    %flag = true;

    l=0;
    diff_cost = 1;
    while(diff_cost>10^(-5))
        l=l+1
        for i=1:size(Ytrain,1)
            i;
            hid_o_tmp = sigmf(hid_theta * Xtrain(i,:)',[1 0]);               %change to i here---->output from hidden layer
            hid_o = [1;hid_o_tmp];
            out_o = sigmf(out_theta * hid_o,[1 0]);
            del_out = out_o.*(1-out_o).*(Y_new(i,:)'-out_o);
            del_hid = (hid_o.*(1-hid_o)).*(out_theta'*del_out);
            del_theta_out = eeta*del_out*hid_o';
            out_theta = out_theta+del_theta_out;             %updating output layer theta
            del_theta_hid = eeta*del_hid(2:size(del_hid,1))*Xtrain(i,:);
            hid_theta = hid_theta+del_theta_hid;             %updating hidden layer theta
        end
        [new_J_theta,final_out] = calcost(hid_theta,Xtrain,out_theta,Y_new);
        diff_cost = J_theta-new_J_theta
        if(diff_cost>0)
            J_theta = new_J_theta
            hid_theta_new = hid_theta;
            out_theta_new = out_theta;
        else
            hid_theta = hid_theta_new;
            out_theta = out_theta_new;
            onrw = ones(1,size(Xtrain,1));
            hid_o_tmp = sigmf(hid_theta * Xtrain',[1 0]);               %change to i here---->output from hidden layer
            hid_o = [onrw;hid_o_tmp];
            final_out = sigmf(out_theta * hid_o,[1 0]);
        end

    end
    [num,train_id]=max(final_out',[],2);
    accuracy_train(j) = sum(train_id==Ytrain)/size(Ytrain,1)*100

    onrw = ones(1,size(Xtest,1));
    hid_o_tmp_test = sigmf(hid_theta * Xtest',[1 0]);               %change to i here---->output from hidden layer
    hid_o_test = [onrw;hid_o_tmp_test];
    test_out = sigmf(out_theta * hid_o_test,[1 0]);
    [num_t,test_id]=max(test_out',[],2);
    accuracy_test(j) = sum(test_id==Ytest)/size(Ytest,1)*100
end
toc
figure();
title('Accuracy against no. of hidden units');
plot(hid_layer,accuracy_test,'r-');
xlabel('no. of hidden units');
ylabel('Accuracy');
