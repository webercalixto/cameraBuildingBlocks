function outImg = setSaturation( img, val )
RGB = getRGB(img);
HSV = rgb2hsv(RGB);
HSV(:, :, 2) = HSV(:, :, 2) * val;
RGB = hsv2rgb(HSV);
outImg = getYUV(RGB);
end

