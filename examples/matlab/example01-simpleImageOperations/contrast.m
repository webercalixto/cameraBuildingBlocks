function imgOut = contrast(  img, myContrast )
Y=img(:,:,1);
U=img(:,:,2);
V=img(:,:,3);
factor = (259*(myContrast+255)) / (255*(259-myContrast)) ;
Y = factor*(Y - 128)+128;
vals = [1:1:255];
valsOut = vals;
valsOut = factor*(valsOut - 128)+128;
valsOut(valsOut>255) = 255;
sTitle = sprintf ('Contrast = %d Factor = %f Equation: Y" = %fx(Y-128)+128 \n',myContrast,factor,factor);
global figPlot
figPlot = figure(9);
plot(vals,valsOut),title(sTitle);
xlim([0 255])
ylim([0 300])
grid on
imgOut = cat(3,Y,U,V);
end

