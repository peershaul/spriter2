#pragma once

class VertexBuffer{
    private:
        unsigned int id, length;
        float* data;
        static unsigned int bound;
    public:
        VertexBuffer();
        void putData(float* data, unsigned int length, bool dynamic);
        void changeData(float* new_data, unsigned int offset, unsigned int size);

        void bind() { s_bind(this); }
        void unbind() { ubind(); }

        static void s_bind(unsigned int id);
        static void s_bind(VertexBuffer* vb) { s_bind(vb->id); }
        static void ubind() { s_bind( (unsigned int) 0 ); }

        static unsigned int get_bound(){ return bound; }
};
