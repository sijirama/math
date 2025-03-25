import { defineConfig } from "vite";
import react from "@vitejs/plugin-react";
import dotenv from "dotenv";

dotenv.config();

const BASE_URL = process.env.VITE_BASE_URL;

export default defineConfig(({ mode }) => ({
  plugins: [react()],
  server:
    mode === "development"
      ? {
          proxy: {
            "/api": {
              target: BASE_URL,
              changeOrigin: true,
              secure: false,
            },
            "/auth": {
              target: BASE_URL,
              changeOrigin: true,
              secure: false,
            },
          },
        }
      : undefined, // No proxy in production
}));
