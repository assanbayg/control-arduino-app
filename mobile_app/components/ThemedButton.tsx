import {
  TouchableOpacity,
  StyleSheet,
  type TouchableOpacityProps,
} from "react-native";
import { useThemeColor } from "@/hooks/useThemeColor";
import { ThemedText, type ThemedTextProps } from "./ThemedText";

export type ThemedButtonProps = TouchableOpacityProps & ThemedTextProps;

export function ThemedButton({
  style,
  lightColor,
  darkColor,
  type = "default",
  children,
  ...rest
}: ThemedButtonProps) {
  const textColor = useThemeColor(
    { light: lightColor, dark: darkColor },
    "text"
  );

  const text = children?.toString();

  return (
    <TouchableOpacity
      style={[
        styles.button,
        style,
        { backgroundColor: text == "ON" ? "green" : "red" },
      ]}
      {...rest}
    >
      <ThemedText style={{ color: "white" }} type={type}>
        {" "}
        {children}
      </ThemedText>
    </TouchableOpacity>
  );
}

const styles = StyleSheet.create({
  button: {
    paddingVertical: 12,
    paddingHorizontal: 24,
    borderRadius: 4,
    alignItems: "center",
    justifyContent: "center",
  },
});
