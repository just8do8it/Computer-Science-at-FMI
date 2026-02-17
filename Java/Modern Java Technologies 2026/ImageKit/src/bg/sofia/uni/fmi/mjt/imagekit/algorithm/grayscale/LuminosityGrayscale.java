package bg.sofia.uni.fmi.mjt.imagekit.algorithm.grayscale;

import java.awt.image.BufferedImage;

import static java.awt.image.BufferedImage.TYPE_INT_RGB;

public class LuminosityGrayscale implements GrayscaleAlgorithm {
    @Override
    public BufferedImage process(BufferedImage image) {
        int width = image.getWidth();
        int height = image.getHeight();

        BufferedImage resImage = new BufferedImage(width, height, TYPE_INT_RGB);

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                int rgb = image.getRGB(j, i);

                double alpha =  (rgb >> 24) & 0xFF;
                double r     =  (rgb >> 16) & 0xFF;
                double g     =  (rgb >> 8)  & 0xFF;
                double b     =   rgb        & 0xFF;

                r *= Math.round(0.21 * r);
                g *= Math.round(0.72 * g);
                b *= Math.round(0.07 * b);
                int grayscaleRGB = ((int)alpha << 24) | ((int)r << 16) | ((int)g << 8) | (int)b;
                resImage.setRGB(j, i, grayscaleRGB);
            }
        }

        return resImage;
    }
}
