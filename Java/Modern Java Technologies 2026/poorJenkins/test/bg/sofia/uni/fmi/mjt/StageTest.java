package bg.sofia.uni.fmi.mjt;
import bg.sofia.uni.fmi.mjt.pipeline.stage.Stage;
import bg.sofia.uni.fmi.mjt.pipeline.step.Step;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class StageTest {

    private static class AddOneStep implements Step<Integer, Integer> {
        @Override
        public Integer process(Integer input) {
            return input + 1;
        }
    }

    private static class ToStringStep implements Step<Integer, String> {
        @Override
        public String process(Integer input) {
            return "v=" + input;
        }
    }

    @Test
    void testStartThrowsWhenInitialStepIsNull() {
        assertThrows(IllegalArgumentException.class,
                () -> Stage.start(null));
    }

    @Test
    void testAddStepThrowsWhenStepIsNull() {
        Stage<Integer, Integer> stage = Stage.start(new AddOneStep());

        assertThrows(IllegalArgumentException.class,
                () -> stage.addStep(null));
    }

    @Test
    void testExecuteRunsSingleStep() {
        Stage<Integer, Integer> stage = Stage.start(new AddOneStep());
        assertEquals(6, stage.execute(5));
    }

    @Test
    void testExecuteRunsMultipleStepsInOrder() {
        Stage<Integer, Integer> stage = Stage
                .start(new AddOneStep())       // 5 -> 6
                .addStep(new AddOneStep())     // 6 -> 7
                .addStep(new AddOneStep());    // 7 -> 8

        assertEquals(8, stage.execute(5));
    }

    @Test
    void testAddStepUpdatesOutputType() {
        Stage<Integer, Integer> numericStage = Stage.start(new AddOneStep());

        Stage<Integer, String> stringStage =
                numericStage.addStep(new ToStringStep());

        String result = stringStage.execute(1);

        assertEquals("v=2", result);
    }
}
