function sliderMoved(src,event)
    value = get(src, 'value') + 1;
    fprintf('novo valor %g\n',value);   
    if value == 1
        global fig2
           try
            close(fig2);
           catch err;
           end
        fig2 = figure;        
        fprintf('Vou abrir imagem 01\n');
        img = imread('C:/Lena01.jpg');
        imshow(img);
    end
    if value == 2
        global fig2
           try
            close(fig2);
           catch err;
           end
        fig2 = figure;        
        fprintf('Vou abrir imagem 02\n');
        img = imread('C:/Lena02.jpg');
        imshow(img);
    end
end
