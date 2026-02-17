package bg.sofia.uni.fmi.mjt.eventbus.events;

import bg.sofia.uni.fmi.mjt.eventbus.events.Payload;

public record SimplePayload<T>(T payload) implements Payload<T> {

    @Override
    public int getSize() {
        return payload == null ? 0 : 1; // or whatever “size” means for you
    }

    @Override
    public T getPayload() {
        return payload;
    }
}
