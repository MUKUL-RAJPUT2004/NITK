import streamlit as st

# EUCLIDEAN ALGORITHM
def gcd(a, b):
    a = abs(a)
    b = abs(b)

    while b != 0:
        r = a % b
        a = b
        b = r

    return a


# EXTENDED EUCLIDEAN ALGORITHM
def extended_gcd(a, b):
    sign_a = 1 if a >= 0 else -1
    sign_b = 1 if b >= 0 else -1

    a = abs(a)
    b = abs(b)

    old_r, r = a, b
    old_x, x = 1, 0
    old_y, y = 0, 1

    while r != 0:
        q = old_r // r

        old_r, r = r, old_r - q * r
        old_x, x = x, old_x - q * x
        old_y, y = y, old_y - q * y

    return old_r, old_x * sign_a, old_y * sign_b


# PAGE
st.set_page_config(
    page_title="Cryptography Calculator",
    page_icon="🔐",
    layout="centered"
)

st.title("🔐 Cryptography Calculator")
st.caption("Euclidean Algorithm • Extended Euclidean Algorithm")
st.divider()

a_text = st.text_input("Enter a", value="7580737102448068849105824714138053941069491157868915804305638022088996559662774386698358381375788407431438490909773919464210849275811995912819526593270607")
b_text = st.text_input("Enter b", value="10026324988889829066485534858501389192155448700188273142578241672800758303724852258555207500772461700286247488498021027641274537248867575929152769996433193")

col1, col2 = st.columns(2)

with col1:
    gcd_button = st.button("GCD", use_container_width=True)

with col2:
    extended_button = st.button("Extended GCD", use_container_width=True)

if gcd_button or extended_button:
    if not a_text.strip() or not b_text.strip():
        st.error("Please enter both numbers.")
    else:
        try:
            a = int(a_text)
            b = int(b_text)

            st.subheader("Input Information")
            c1, c2 = st.columns(2)

            with c1:
                st.metric("Bit length of a", a.bit_length())

            with c2:
                st.metric("Bit length of b", b.bit_length())

            if a.bit_length() == 512:
                st.success("✓ a is exactly 512-bit")
            else:
                st.info("a is not exactly 512-bit")

            if b.bit_length() == 512:
                st.success("✓ b is exactly 512-bit")
            else:
                st.info("b is not exactly 512-bit")

            if gcd_button:
                result = gcd(a, b)
                st.subheader("GCD Result")
                st.success(f"GCD(a, b) = {result}")

            if extended_button:
                result, x, y = extended_gcd(a, b)
                verification = a * x + b * y

                st.subheader("Extended GCD Result")
                st.write(f"**GCD = {result}**")
                st.write(f"**x = {x}**")
                st.write(f"**y = {y}")

                st.subheader("Bézout Verification")
                st.code(f"{a} × ({x}) + {b} × ({y}) = {verification}")

                if verification == result:
                    st.success("✓ Verification PASSED: ax + by = GCD")
                else:
                    st.error("✗ Verification FAILED")

        except ValueError:
            st.error("Please enter valid integers.")
