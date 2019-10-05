function [ rgb ] = getRGB( img )
%GETRGB Summary of this function goes here
%   Detailed explanation goes here
Y=img(:,:,1);
U=img(:,:,2);
V=img(:,:,3);
R = Y + 1.139834576 * V;
G = Y -.3946460533 * U -.58060 * V;
B = Y + 2.032111938 * U;
rgb = cat(3,R,G,B);

end

