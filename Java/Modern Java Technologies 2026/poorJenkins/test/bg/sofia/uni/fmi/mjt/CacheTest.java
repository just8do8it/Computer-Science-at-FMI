package bg.sofia.uni.fmi.mjt;

import bg.sofia.uni.fmi.mjt.file.File;
import bg.sofia.uni.fmi.mjt.file.step.UpperCaseFile;
import bg.sofia.uni.fmi.mjt.pipeline.Cache;
import bg.sofia.uni.fmi.mjt.pipeline.Pipeline;
import bg.sofia.uni.fmi.mjt.pipeline.stage.Stage;
import org.junit.jupiter.api.Test;

import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

class CacheTest {

    @Test
    void testCacheStoresAndRetrievesValue() {
        Cache cache = new Cache();
        String key = "k";
        Integer value = 42;

        cache.cacheValue(key, value);

        assertTrue(cache.containsKey(key));
        assertEquals(value, cache.getCachedValue(key));
        assertFalse(cache.isEmpty());
    }

    @Test
    void testCacheOverridesExistingValueForSameKey() {
        Cache cache = new Cache();
        String key = "k";

        cache.cacheValue(key, 1);
        cache.cacheValue(key, 2);

        assertEquals(2, cache.getCachedValue(key));
    }

    @Test
    void testGetCachedValueReturnsNullForMissingKey() {
        Cache cache = new Cache();

        assertNull(cache.getCachedValue("missing"));
    }

    @Test
    void testClearEmptiesTheCache() {
        Cache cache = new Cache();
        cache.cacheValue("k", 1);

        cache.clear();

        assertTrue(cache.isEmpty());
        assertFalse(cache.containsKey("k"));
    }

    @Test
    void testContainsKeyAfterPipelineExecute() {
        Cache cache = new Cache();
        Stage<File, File> stage = Stage.start(new UpperCaseFile());
        Pipeline<File, File> pipeline = new Pipeline<>(List.of(stage), cache);

        String filename = "new file";
        File file = new File(filename);
        pipeline.execute(file);

        assertTrue(cache.containsKey(file));
    }
}
