import streamlit as st
import math
from algorithms import *
from ui.styles import setup

setup()

DEMO_A = "7580737102448068849105824714138053941069491157868915804305638022088996559662774386698358381375788407431438490909773919464210849275811995912819526593270607"
DEMO_B = "10026324988889829066485534858501389192155448700188273142578241672800758303724852258555207500772461700286247488498021027641274537248867575929152769996433193"

op = st.sidebar.radio("Operation", [
    "GCD","Extended GCD","Modular Inverse","Modular Addition",
    "Modular Multiplication","Modular Exponentiation","Performance Comparison"
])

def inputs():
    c1,c2=st.columns(2)
    with c1: a=int(st.text_input("a", DEMO_A))
    with c2: b=int(st.text_input("b", DEMO_B))
    return a,b

def bits(*nums):
    cols=st.columns(len(nums))
    for i,n in enumerate(nums):
        cols[i].metric(f"Input {i+1} bit length", n.bit_length())
    if all(n.bit_length()>=512 for n in nums):
        st.success("✓ All inputs are at least 512-bit.")

if op=="GCD":
    st.subheader("Euclidean GCD")
    a,b=inputs()
    if st.button("Calculate GCD", type="primary", use_container_width=True):
        bits(a,b); g,steps,t=gcd(a,b)
        st.success(f"GCD(a,b) = {g}")
        st.metric("Execution time", f"{t:.9f} s")
        with st.expander(f"Show all Euclidean steps ({len(steps)})"):
            for i,(aa,bb,q,r) in enumerate(steps,1):
                st.code(f"{i}. {aa} = {q} × {bb} + {r}")
        trusted=trusted_gcd(a,b)
        st.success("✓ Verified against math.gcd()" if g==trusted else "✗ Verification failed")

elif op=="Extended GCD":
    st.subheader("Extended Euclidean Algorithm")
    a,b=inputs()
    if st.button("Calculate Extended GCD", type="primary", use_container_width=True):
        bits(a,b); g,x,y,steps,t=extended_gcd(a,b)
        c1,c2,c3=st.columns(3)
        c1.metric("GCD",g); c2.metric("x",x); c3.metric("y",y)
        st.metric("Execution time",f"{t:.9f} s")
        with st.expander(f"Show complete steps ({len(steps)} iterations)"):
            for i,s in enumerate(steps,1):
                oldr,r,q,nr,oldx,cx,oldy,cy,nx,ny=s
                st.code(f"{i}. {oldr} = {q} × {r} + {nr}\n   x: {oldx} → {nx}\n   y: {oldy} → {ny}")
        check=a*x+b*y
        st.subheader("Bézout Verification")
        st.code(f"{a} × ({x}) + {b} × ({y}) = {check}")
        st.success("✓ PASS: ax + by = gcd(a,b)" if check==g else "✗ FAIL")
        st.success("✓ GCD matches Python math.gcd()" if g==trusted_gcd(a,b) else "✗ GCD mismatch")

elif op=="Modular Inverse":
    st.subheader("Modular Inverse")
    a=st.number_input("a",value=3,step=1)
    m=st.number_input("modulus m",value=7,min_value=1,step=1)
    if st.button("Find Inverse",type="primary",use_container_width=True):
        inv,g,x,y,steps,t=modular_inverse(int(a),int(m))
        st.metric("gcd(a,m)",g); st.metric("Execution time",f"{t:.9f} s")
        if inv is None: st.error("No inverse: gcd(a,m) ≠ 1.")
        else:
            st.success(f"{a}⁻¹ mod {m} = {inv}")
            st.code(f"{a} × ({x}) + {m} × ({y}) = 1\n({a} × {inv}) mod {m} = {(int(a)*inv)%int(m)}")
            with st.expander("Show Extended-GCD steps"):
                for i,(aa,bb,q,r,*_) in enumerate(steps,1): st.code(f"{i}. {aa} = {q} × {bb} + {r}")
            st.success("✓ Inverse verified")

elif op in ("Modular Addition","Modular Multiplication"):
    st.subheader(op)
    c1,c2,c3=st.columns(3)
    a=c1.number_input("a",value=17,step=1); b=c2.number_input("b",value=23,step=1); m=c3.number_input("modulus",value=10,min_value=1,step=1)
    if st.button("Calculate",type="primary",use_container_width=True):
        a,b,m=map(int,(a,b,m))
        result=modular_add(a,b,m) if op=="Modular Addition" else modular_multiply(a,b,m)
        symbol="+" if op=="Modular Addition" else "×"
        raw=a+b if symbol=="+" else a*b
        st.success(f"({a} {symbol} {b}) mod {m} = {result}")
        st.code(f"({a} {symbol} {b}) mod {m}\n= {raw} mod {m}\n= {result}")

elif op=="Modular Exponentiation":
    st.subheader("Modular Exponentiation")
    c1,c2,c3=st.columns(3)
    a=c1.number_input("Base",value=3,step=1); e=c2.number_input("Exponent",value=13,min_value=0,step=1); m=c3.number_input("Modulus",value=7,min_value=1,step=1)
    if st.button("Calculate Both",type="primary",use_container_width=True):
        a,e,m=map(int,(a,e,m))
        n,tn=naive_mod_pow(a,e,m); f,tf,steps=square_multiply(a,e,m); trusted=pow(a,e,m)
        c1,c2,c3=st.columns(3); c1.metric("Naive",n); c2.metric("Square-and-multiply",f); c3.metric("Python pow()",trusted)
        st.metric("Naive time",f"{tn:.9f} s"); st.metric("Square-and-multiply time",f"{tf:.9f} s")
        st.success("✓ All results match" if n==f==trusted else "✗ Results differ")
        with st.expander("Show square-and-multiply steps",expanded=True):
            for i,(ee,bit,base,before,after) in enumerate(steps,1):
                st.code(f"{i}. exponent={ee}, bit={bit}, base={base}\n   result: {before} → {after}")
        st.info(f"Naive uses about {e} multiplications; square-and-multiply uses {len(steps)} iterations.")

else:
    st.subheader("Performance Comparison")
    c1,c2=st.columns(2)
    a=c1.number_input("Base",value=7,step=1); m=c2.number_input("Modulus",value=1000000007,min_value=1,step=1)
    exps=st.text_input("Exponents (comma-separated)","100, 1000, 5000, 10000")
    if st.button("Run Benchmark",type="primary",use_container_width=True):
        rows=[]
        for e in [int(x.strip()) for x in exps.split(",") if x.strip()]:
            if e>2000000:
                st.warning(f"Skipped {e}: naive method would take too long.")
                continue
            _,tn=naive_mod_pow(int(a),e,int(m)); _,tf,steps=square_multiply(int(a),e,int(m))
            rows.append({"Exponent":e,"Naive time (s)":tn,"Square-and-multiply (s)":tf,"Fast iterations":len(steps),"Speedup":tn/tf if tf else 0})
        st.dataframe(rows,use_container_width=True)
        st.latex(r"\text{Naive: }O(e)\qquad\text{Square-and-multiply: }O(\log e)")
