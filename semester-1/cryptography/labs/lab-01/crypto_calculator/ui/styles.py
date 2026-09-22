import streamlit as st

def setup():
    st.set_page_config(page_title="Cryptography Calculator", page_icon="🔐", layout="wide")
    st.markdown("""
    <style>
    .title {font-size:2.5rem;font-weight:800;margin-bottom:0}
    .sub {color:#667085;margin-bottom:1rem}
    </style>
    """, unsafe_allow_html=True)
    st.markdown('<div class="title">🔐 Cryptography Calculator</div>', unsafe_allow_html=True)
    st.markdown('<div class="sub">Lab 1 · Modular Arithmetic & Extended Euclidean Algorithm</div>', unsafe_allow_html=True)
    st.divider()
