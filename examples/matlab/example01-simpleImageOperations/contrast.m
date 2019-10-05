function imgOut = contrast(  img, myContrast )
Y=img(:,:,1);
U=img(:,:,2);
V=img(:,:,3);
factor = (259*(myContrast+255)) / (255*(259-myContrast)) ;
Y = factor*(Y - 128)+128;
imgOut = cat(3,Y,U,V);
end

