%% definition: https://en.wikipedia.org/wiki/Gamma_correction
function [ imgOut ] = powerLaw( img, c, gamma )
Y=img(:,:,1);
U=img(:,:,2);
V=img(:,:,3);
Y=255*c*(Y/255).^(gamma);
if gamma == 1
    
else
    %%U = Y*0;
    %%V =Y*0;
end
vals = [1:1:255];
valsOut = vals;
valsOut=255*c*(valsOut/255).^(gamma);
global figPlot
figPlot = figure(9);
plot(vals,valsOut);
grid on, axis equal
imgOut = cat(3,Y,U,V);
end

