# Cryptography Calculator

Python + Streamlit implementation of:
- Euclidean Algorithm
- Extended Euclidean Algorithm
- Bézout identity verification
- 512-bit input detection

Run:
```text
py -m pip install streamlit
py -m streamlit run app.py
```

The app starts with two exactly 512-bit demo numbers.

a = 7580737102448068849105824714138053941069491157868915804305638022088996559662774386698358381375788407431438490909773919464210849275811995912819526593270607

b = 10026324988889829066485534858501389192155448700188273142578241672800758303724852258555207500772461700286247488498021027641274537248867575929152769996433193

Both have `bit_length() == 512`.
Python's built-in `int` supports arbitrary-precision integers.
