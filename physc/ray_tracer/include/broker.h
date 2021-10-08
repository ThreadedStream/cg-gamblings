#pragma once

#define GOTO_COND(cond, success, fallback) \
    if ((cond)) { goto success; } else { goto fallback; }


class Broker{
public:
    template<typename In, typename Out>
    static Out* convert(const In* ins, int32_t count)  {
        bool to_sdl = std::is_same<In, b2Vec2>::value;
        Out* outs = static_cast<Out*>(malloc(sizeof(Out)));

        GOTO_COND(to_sdl, cvt_to_sdl, cvt_to_b2vec2);
        // TODO(threadedstream): place it outside a class?
        cvt_to_sdl:
        for (int32_t i = 0; i < count; ++i) {
            outs[i] = {(int) ins[i].x, (int) ins[i].y};
        }
        goto ret;

        cvt_to_b2vec2:
        for (int32_t i = 0; i < count; ++i) {
            outs[i] = Out{(float) ins[i].x, (float) ins[i].y};
        }
        goto ret;

        ret:
        return outs;
    }
};
