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

                int    a = (rgb >> 24) & 0xFF;
                double r = (rgb >> 16) & 0xFF;
                double b = (rgb >>  8) & 0xFF;
                double g =  rgb        & 0xFF;

                r = 0.21 * r;
                g = 0.72 * g;
                b = 0.07 * b;

                double averageBeforeAmplification  = (r + g + b) / 3;
                double averageCoefficientForAmplification = (0.21 + 0.72 + 0.07) / 3;
                double averageAfterAmplification = averageBeforeAmplification / averageCoefficientForAmplification;
                int average = (int) averageAfterAmplification;

                int grayscaleRGB = (a << 24) |
                        (average << 16) |
                        (average << 8) |
                         average;
                resImage.setRGB(j, i, grayscaleRGB);
            }
        }

        return resImage;
    }
}
