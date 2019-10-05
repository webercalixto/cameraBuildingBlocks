function imgOut  = brightness( img, bright )
Y=img(:,:,1);
U=img(:,:,2);
V=img(:,:,3);
Y = Y+bright;
imgOut = cat(3,Y,U,V);
end

