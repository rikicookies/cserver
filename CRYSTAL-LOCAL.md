# Crystal Server 15.30 local

Esta copia incluye el código, el datapack y `crystalserver.exe` de Windows. Copia `config.local.example.lua` como `config.lua` y completa la conexión a MySQL local. Conserva la base de una instalación existente.

En una base nueva, importa `schema.sql` y usa `database/bots/schema-crystal.sql` para las tablas de bots. Los archivos `seed-crystal*.sql` son datos preparados para el mundo local original. Revisa los IDs de mundo, casas y personajes antes de aplicarlos a otra base.

Ejecuta `crystalserver.exe` desde la raíz del repositorio. El ejemplo configura el mundo en `127.0.0.1:7482`.
