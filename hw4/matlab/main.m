%% 16*16
clear all; close all;
fileID = fopen('test1','r');
formatSpec = '%d';
A = fscanf(fileID,formatSpec);
fclose(fileID);
len = A(1);     % store the 
A(1) = [];      
A(1) = [];
A(257) = [];
A(257) = [];

A1 = A(1:len^2);
A2 = A(len^2+1:size(A,1));
a = transpose(reshape(A1,[len,len]));
b = transpose(reshape(A2,[len,len]));

in_built(a,b);
triloop(a,b);
par_loop(a,b);
disp('Strassen with parallel')
tic
strassenw(a,b,8);
toc

%% 1024*1024
clear all; close all;
fileID = fopen('test2','r');
formatSpec = '%d';
A = fscanf(fileID,formatSpec);
fclose(fileID);
len = A(1);     % store the 
A(1) = [];      
A(1) = [];
A(257) = [];
A(257) = [];

A1 = A(1:len^2);
A2 = A(len^2+1:size(A,1));
a = transpose(reshape(A1,[len,len]));
b = transpose(reshape(A2,[len,len]));

in_built(a,b);
triloop(a,b);
par_loop(a,b);
disp('Strassen with parallel')
tic
strassenw(a,b,1024);
toc

%% 4096*4096
clear all; close all;
fileID = fopen('test3','r');
formatSpec = '%d';
A = fscanf(fileID,formatSpec);
fclose(fileID);
len = A(1);     % store the 
A(1) = [];      
A(1) = [];
A(257) = [];
A(257) = [];

A1 = A(1:len^2);
A2 = A(len^2+1:size(A,1));
a = transpose(reshape(A1,[len,len]));
b = transpose(reshape(A2,[len,len]));

in_built(a,b);
triloop(a,b);
par_loop(a,b);
disp('Strassen with parallel')
tic
strassenw(a,b,4096);
toc
