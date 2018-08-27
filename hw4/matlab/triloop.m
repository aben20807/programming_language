function C = triloop(A,B)
    disp('For loop without parallel')
    C = zeros(length(A),length(A));
    tic
    for i = 1:length(A)
        for j = 1:length(A)
            for k = 1:length(A)
                C(i,j) = C(i,j) + A(i,k) * B(k,j);
            end
        end
    end
    toc
end