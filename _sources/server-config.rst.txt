####################
Server Configuration
####################

==========
Components
==========

+----------------+----------------------------------------+--------------------------------+--------------------------------------+-------------------------------------+
| Name           | Description                            | DockerHub Image                | Volumes                              | TCP Port Mapping (Public:Private)   |
+================+========================================+================================+======================================+=====================================+
| PostgreSQL     | Database of choice for storing and     | ``postgres:latest``            | ``pgdata:/var/lib/postgresql/data``  | ``5432:5432``                       |
|                | retrieving water quality measurements. |                                |                                      |                                     |
+----------------+----------------------------------------+--------------------------------+--------------------------------------+-------------------------------------+
| pgAdmin4       | Web interface for easily interacting   | ``dpage/pgadmin4:latest``      |                                      | ``4000:80``                         |
| (Optional)     | with PostgreSQL databases.             |                                |                                      |                                     |
+----------------+----------------------------------------+--------------------------------+--------------------------------------+-------------------------------------+
| PostgREST      | REST API for interacting with          | ``postgrest/postgrest:latest`` |                                      | ``3000:3000``                       |
|                | PostgreSQL databases.                  |                                |                                      |                                     |
+----------------+----------------------------------------+--------------------------------+--------------------------------------+-------------------------------------+
| Grafana        | Web app for creating and viewing data  | ``grafana/grafana-oss:latest`` | ``grafana-storage:/var/lib/grafana`` | ``8000:5432``                       |
|                | visualizations from database.          |                                |                                      |                                     |
+----------------+----------------------------------------+--------------------------------+--------------------------------------+-------------------------------------+

=====
Usage
=====

Run ``docker-compose -f docker/compose.yml up [--detach]`` to initialize all server components.

- The ``--detach`` option starts the containers in the background and leaves them running.

Run ``docker-compose -f docker/compose.yml down [-v]`` to shut down all server components.

- The ``-v`` option wipes all persistent volumes (**WARNING**: This deletes all PostgreSQL and Grafana data -- use only when completely resetting server).

==============
Docker-Compose
==============

The following Docker-Compose file is used to define all the necessary server components:

.. literalinclude:: ../docker/compose.yml
    :language: yaml
    :linenos:
    :caption:
