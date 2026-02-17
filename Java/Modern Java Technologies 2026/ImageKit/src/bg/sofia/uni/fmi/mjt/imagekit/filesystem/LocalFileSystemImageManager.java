package bg.sofia.uni.fmi.mjt.imagekit.filesystem;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.nio.file.DirectoryIteratorException;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;
import static javax.imageio.ImageIO.read;
import static javax.imageio.ImageIO.write;

public class LocalFileSystemImageManager implements FileSystemImageManager {
    @Override
    public BufferedImage loadImage(File imageFile) throws IOException {
        if (imageFile == null) {
            throw new IllegalArgumentException("File is NULL!");
        }
        return read(imageFile);
    }

    @Override
    public List<BufferedImage> loadImagesFromDirectory(File imagesDirectory) throws IOException {
        List<BufferedImage> images = new ArrayList<>();

        Path dirPath = Path.of(imagesDirectory.getPath(), File.separator);
        int illegalFilesCnt = 0;
        int filesCount = 0;
        try (DirectoryStream<Path> stream = Files.newDirectoryStream(dirPath)) {
            for (Path fileOrSubDir : stream) {
                if (    fileOrSubDir.endsWith(".png") ||
                        fileOrSubDir.endsWith(".jpg") ||
                        fileOrSubDir.endsWith(".jpeg") ||
                        fileOrSubDir.endsWith(".webp")) {
                    images.add(loadImage(new File(String.valueOf(fileOrSubDir))));
                }
                else {
                    illegalFilesCnt++;
                }
                filesCount++;
            }
        } catch (IOException | DirectoryIteratorException e) {
            throw new IllegalArgumentException("Corrupt directory file!");
        }

        if (illegalFilesCnt == filesCount) {
            throw new IOException("Not an image in sight!");
        }

        return images;
    }

    @Override
    public void saveImage(BufferedImage image, File imageFile) throws IOException {
        if (image == null || imageFile == null) {
            throw new IllegalArgumentException("image and imageFile must not be null!");
        }

        String name = imageFile.getName();
        int dotIndex = name.lastIndexOf('.');
        if (dotIndex <= 0 || dotIndex > name.length() - 3) {
            throw new IllegalArgumentException("imageFile isn't of the right format!");
        }
        String formatExtension = name.substring(dotIndex + 1);

        // Make sure parent directory exists
        File parent = imageFile.getParentFile();
        if (parent != null && !parent.exists() && !parent.mkdirs()) {
            throw new IOException("Could not create directory: " + parent);
        }

        if (!write(image, formatExtension, imageFile)) {
            throw new IOException("No writer found for format: " + formatExtension);
        }
    }
}
