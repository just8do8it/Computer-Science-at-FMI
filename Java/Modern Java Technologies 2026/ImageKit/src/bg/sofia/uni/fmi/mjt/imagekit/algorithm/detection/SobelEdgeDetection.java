package bg.sofia.uni.fmi.mjt.imagekit.algorithm.detection;

import java.awt.image.BufferedImage;
import bg.sofia.uni.fmi.mjt.imagekit.algorithm.ImageAlgorithm;

import static java.awt.image.BufferedImage.TYPE_INT_RGB;

public class SobelEdgeDetection implements EdgeDetectionAlgorithm {
    private final ImageAlgorithm grayscaleAlgorithm;

    public SobelEdgeDetection(ImageAlgorithm grayscaleAlgorithm) {
        this.grayscaleAlgorithm = grayscaleAlgorithm;
    }

    private int[][] CreateGreyscaleIntensityMatrix(BufferedImage greyscaleImage, int height, int width) {
        // The matrix has 2 extra rows and columns filled with 0's, because
        // we'll need 3x3 matrices from every "real" pixel, and we'll use
        // the 0's as filler
        int[][] intensity = new int[height + 2][width + 2];

        for (int y = 0; y < height + 2; y++) {
            for (int x = 0; x < width + 2; x++) {
                if (x == 0 || x == width + 1 ||
                        y == 0 || y == height + 1) {
                    intensity[y][x] = 0;
                    continue;
                }
                int rgb = greyscaleImage.getRGB(x - 1, y - 1);

                int greyscaleIntensity = (rgb >> 16) & 0xFF;
                intensity[y][x] = greyscaleIntensity;
            }
        }

        return intensity;
    }
    @Override
    public BufferedImage process(BufferedImage image) {
        BufferedImage greyscaleImage = grayscaleAlgorithm.process(image);
        int width = image.getWidth();
        int height = image.getHeight();

        int[][] intensity = CreateGreyscaleIntensityMatrix(greyscaleImage, height, width);

        // Horizontal Sobel Kernel
        int[][] Gx = {
                {-1, 0, 1},
                {-2, 0, 2},
                {-1, 0, 1}
        };

        // Vertical Sobel Kernel
        int[][] Gy = {
                {-1, -2, -1},
                {0, 0, 0},
                {1, 2, 1}
        };

        BufferedImage edgeDetectedImage = new BufferedImage(width, height, TYPE_INT_RGB);

        for (int i = 1; i < height; i++) {
            for (int j = 1; j < width; j++) {
                int[][] pixelMatrix = {
                        {intensity[i - 1][j - 1], intensity[i - 1][j], intensity[i - 1][j + 1]},
                        {intensity[i][j - 1], intensity[i][j], intensity[i][j + 1]},
                        {intensity[i + 1][j - 1], intensity[i + 1][j], intensity[i + 1][j + 1]}
                };

                int horizontalSum = 0;
                int verticalSum = 0;
                for (int row = 0; row < 3; row++) {
                    for (int col = 0; col < 3; col++) {
                        int internalHorizontalsum = 0;
                        int internalVerticalsum = 0;
                        for (int k = 0; k < 3; k++) {
                            internalHorizontalsum += pixelMatrix[row][col] * Gx[row][col];
                            internalVerticalsum += pixelMatrix[row][col] * Gy[row][col];
                        }
                        horizontalSum += internalHorizontalsum;
                        verticalSum += internalVerticalsum;
                    }
                }

                double gValue = Math.sqrt(Math.pow(horizontalSum, 2) + Math.pow(verticalSum, 2));
                int pixelValue = Math.min(255, (int) Math.round(gValue));
                int rgb = (pixelValue << 16) | (pixelValue << 8) | pixelValue;
                edgeDetectedImage.setRGB(j, i, rgb);
            }
        }

        return edgeDetectedImage;
    }
}
