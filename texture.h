#ifndef path_tracer_texture_h
#define path_tracer_texture_h

class Texture {
public:
    virtual Vec3 value(float u, float v, const Vec3& p) const = 0;
};


class ConstantTexture : public Texture {
public:
    Vec3 color;

    ConstantTexture() {}
    ConstantTexture(Vec3 c) : color(c) {}
    
    virtual Vec3 value(float u, float v, const Vec3& p) const {
        return color;
    }
};


class CheckerTexture : public Texture {
public:
    CheckerTexture() {}
    CheckerTexture(Texture* t0, Texture* t1) : even(t0), odd(t1) {}
    
    virtual Vec3 value(float u, float v, const Vec3& p) const {
        float t = 10.0f;
        float sines = sin(sin(t * p.x()) * sin(t * p.y()) * sin(t * p.z()));
        
        if (sines > 0) {
            return odd->value(u, v, p);
        }
        
        return even->value(u, v, p);
    }

    Texture* even;
    Texture* odd;
};

#endif
