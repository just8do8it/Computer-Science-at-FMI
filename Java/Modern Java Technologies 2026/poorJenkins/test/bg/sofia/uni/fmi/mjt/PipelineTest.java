package bg.sofia.uni.fmi.mjt;

import bg.sofia.uni.fmi.mjt.pipeline.Cache;
import bg.sofia.uni.fmi.mjt.pipeline.Pipeline;
import bg.sofia.uni.fmi.mjt.pipeline.stage.Stage;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;

import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.*;

@ExtendWith(MockitoExtension.class)
class PipelineTest {

    @Mock
    private Cache cache;

    @Mock
    private Stage<Object, Object> firstStage;

    @Mock
    private Stage<Object, Object> secondStage;

    private Pipeline<String, String> createPipelineWithStages() {
        List<Stage<?, ?>> stages = new ArrayList<>();
        stages.add(firstStage);
        stages.add(secondStage);
        return new Pipeline<>(stages, cache);
    }

    @Test
    void testExecuteRunsAllStagesAndCachesResultWhenNotCached() {
        String input = "input";
        String mid = "mid";
        String output = "out";

        Pipeline<String, String> pipeline = createPipelineWithStages();

        when(cache.containsKey(input)).thenReturn(false);
        when(firstStage.execute(input)).thenReturn(mid);
        when(secondStage.execute(mid)).thenReturn(output);

        String result = pipeline.execute(input);

        assertEquals(output, result);

        verify(cache).containsKey(input);
        verify(firstStage).execute(input);
        verify(secondStage).execute(mid);
        verify(cache).cacheValue(input, output);
        verifyNoMoreInteractions(cache, firstStage, secondStage);
    }

    @Test
    void testExecuteUsesCachedValueAndSkipsStagesWhenPresent() {
        String input = "input";
        String cached = "cached";

        Pipeline<String, String> pipeline = createPipelineWithStages();

        when(cache.containsKey(input)).thenReturn(true);
        when(cache.getCachedValue(input)).thenReturn(cached);

        String result = pipeline.execute(input);

        assertEquals(cached, result);

        verify(cache).containsKey(input);
        verify(cache).getCachedValue(input);
        verifyNoInteractions(firstStage, secondStage);
        verifyNoMoreInteractions(cache);
    }

    @Test
    void testExecuteCallsStagesOnlyOnceForSameInput() {
        String input = "input";
        String mid = "mid";
        String output = "out";

        List<Stage<?, ?>> stages = new ArrayList<>();
        stages.add(firstStage);
        Pipeline<String, String> pipeline = new Pipeline<>(stages, cache);

        when(cache.containsKey(input))
                .thenReturn(false)
                .thenReturn(true);

        when(firstStage.execute(input)).thenReturn(mid);
        when(cache.getCachedValue(input)).thenReturn(output);

        String first = pipeline.execute(input);
        String second = pipeline.execute(input);

        assertEquals(mid, first);
        assertEquals(output, second);

        verify(firstStage, times(1)).execute(input);
        verify(cache, times(1)).cacheValue(input, mid);
    }

    @Test
    @SuppressWarnings("unchecked")
    void testAddStageAddsStageAndIsUsedOnExecute() {
        String input = "input";
        String afterFirst = "afterFirst";
        String afterSecond = "afterSecond";

        List<Stage<?, ?>> stages = new ArrayList<>();
        stages.add(firstStage);

        Pipeline<String, String> pipeline = new Pipeline<>(stages, cache);

        Pipeline<String, Object> samePipeline = pipeline.addStage(secondStage);


        assertSame(pipeline, samePipeline);

        when(cache.containsKey(input)).thenReturn(false);
        when(firstStage.execute(input)).thenReturn(afterFirst);
        when(secondStage.execute(afterFirst)).thenReturn(afterSecond);

        String result = (String) samePipeline.execute(input);

        assertEquals(afterSecond, result);
        verify(firstStage).execute(input);
        verify(secondStage).execute(afterFirst);
    }

    @Test
    void testExecutePropagatesExceptionFromStageAndDoesNotCache() {
        String input = "input";
        RuntimeException failure = new RuntimeException("boom");

        List<Stage<?, ?>> stages = new ArrayList<>();
        stages.add(firstStage);

        Pipeline<String, String> pipeline = new Pipeline<>(stages, cache);

        when(cache.containsKey(input)).thenReturn(false);
        when(firstStage.execute(input)).thenThrow(failure);

        RuntimeException thrown = assertThrows(RuntimeException.class,
                () -> pipeline.execute(input));

        assertSame(failure, thrown);
        verify(cache, never()).cacheValue(any(), any());
    }
}
